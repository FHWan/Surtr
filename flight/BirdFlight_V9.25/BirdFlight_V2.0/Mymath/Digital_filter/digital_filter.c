/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech *********************
 * 作者 	:Xiluna Tech
 * 文件名 :digital_filter.c
 * 描述   :FIR数字滤波器
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
******************************************************************************/
#include  "digital_filter.h"
#include  <math.h>
#include  "arm_math.h"
#include  <stdint.h>

// Found at http://paulbourke.net/miscellaneous//dft/
void filter_fft(int dir, int m, float *real, float *imag) {
	long n,i,i1,j,k,i2,l,l1,l2;
	float c1,c2,tx,ty,t1,t2,u1,u2,z;

	// Calculate the number of points
	n = 1 << m;

	// Do the bit reversal
	i2 = n >> 1;
	j = 0;
	for (i=0;i<n-1;i++) {
		if (i < j) {
			tx = real[i];
			ty = imag[i];
			real[i] = real[j];
			imag[i] = imag[j];
			real[j] = tx;
			imag[j] = ty;
		}
		k = i2;
		while (k <= j) {
			j -= k;
			k >>= 1;
		}
		j += k;
	}

	// Compute the FFT
	c1 = -1.0;
	c2 = 0.0;
	l2 = 1;
	for (l=0;l<m;l++) {
		l1 = l2;
		l2 <<= 1;
		u1 = 1.0;
		u2 = 0.0;
		for (j=0;j < l1;j++) {
			for (i=j;i < n;i += l2) {
				i1 = i + l1;
				t1 = u1 * real[i1] - u2 * imag[i1];
				t2 = u1 * imag[i1] + u2 * real[i1];
				real[i1] = real[i] - t1;
				imag[i1] = imag[i] - t2;
				real[i] += t1;
				imag[i] += t2;
			}
			z =  u1 * c1 - u2 * c2;
			u2 = u1 * c2 + u2 * c1;
			u1 = z;
		}
		c2 = sqrt((1.0f - c1) / 2.0f);
		if (dir) {
			c2 = -c2;
		}
		c1 = sqrt((1.0f + c1) / 2.0f);
	}

	// Scaling for reverse transform
	if (dir) {
		for (i=0;i < n;i++) {
			real[i] /= n;
			imag[i] /= n;
		}
	}
}

// Found at http://paulbourke.net/miscellaneous//dft/
void filter_dft(int dir, int len, float *real, float *imag) {
	long i,k;
	float arg;
	float cosarg, sinarg;

	if(dir) {
		dir = 1;
	} else {
		dir = -1;
	}

	float x2[len];
	float y2[len];

	for (i=0;i < len;i++) {
		x2[i] = 0;
		y2[i] = 0;
		arg = -(float)dir * 2.0f * PI * (float)i / (float)len;
		for (k=0;k<len;k++) {
			cosarg = cosf(k * arg);
			sinarg = sinf(k * arg);
			x2[i] += (real[k] * cosarg - imag[k] * sinarg);
			y2[i] += (real[k] * sinarg + imag[k] * cosarg);
		}
	}

	// Copy the data back
	if (dir == 1) {
		for (i=0;i<len;i++) {
			real[i] = x2[i] / (float)len;
			imag[i] = y2[i] / (float)len;
		}
	} else {
		for (i=0;i<len;i++) {
			real[i] = x2[i];
			imag[i] = y2[i];
		}
	}
}

void filter_fftshift(float *data, int len) {
	for (int i = 0;i < (len / 2);i++) {
		float r1 = data[i];
		float r2 = data[len/2 + i];

		data[i] = r2;
		data[len / 2 + i] = r1;
	}
}

void filter_hamming(float *data, int len) {
	if (len % 2 == 0) {
		for (int i = 0;i < (len / 2);i++) {
			float val = 0.54f - 0.46f * cosf((2.0f * PI * (float)i)/(float)(len - 1));
			data[i] *= val;
			data[len - i - 1] *= val;
		}
	} else {
		for (int i = 0;i < len;i++) {
			data[i] *= 0.54f - 0.46f * cosf((2.0f * PI * (float)i)/(float)(len - 1));
		}
	}
}

void filter_zeroPad(float *data, float *result, int dataLen, int resultLen) {
	for (int i = 0;i < resultLen;i++) {
		if (i < dataLen) {
			result[i] = data[i];
		} else {
			result[i] = 0;
		}
	}
}

void filter_create_fir_lowpass(float *filter_vector, float f_break, int bits, int use_hamming) {
	int taps = 1 << bits;
	float imag[taps];

	for(int i = 0;i < taps;i++) {
		if (i < (int)((float)taps * f_break)) {
			filter_vector[i] = 1;
		} else {
			filter_vector[i] = 0;
		}
		imag[i] = 0;
	}

	// Make filter symmetric
	for (int i = 0;i < taps / 2;i++) {
		filter_vector[taps - i - 1] = filter_vector[i];
	}

	filter_fft(1, bits, filter_vector, imag);
	filter_fftshift(filter_vector, taps);

	if (use_hamming) {
		filter_hamming(filter_vector, taps);
	}
}

/*
 * Run FIR filter iteration.
 *
 * bits: A power of two representing the length of the filter
 * filter: The FIR filter coefficients
 * offset: an offset into the vector buffer. Will wrap around when going past
 * length while filtering. Useful for keeping a circular buffer with samples
 * and avoiding to shift the whole buffer.
 *
 * returns: The filtered result sample.
 */
float filter_run_fir_iteration(float *vector, float *filter, int bits, uint32_t offset) {
	float result = 0;
	int size = 1 << bits;
	uint32_t cnt_mask = 0xFFFFFFFF >> (32 - bits);

	for (int i = 0;i < size;i++) {
		result += filter[i] * vector[offset];
		offset++;
		offset &= cnt_mask;
	}

	return result;
}

/**
 * Add sample to buffer
 * @param buffer
 * The buffer to add the sample to
 * @param sample
 * The sample to add
 * @param bits
 * The length of the buffer in bits
 * @param offset
 * Pointer to the current offset in the buffer. Will be updated in this call
 * and wrapped at the length of this buffer.
 */
void filter_add_sample(float *buffer, float sample, int bits, uint32_t *offset) {
	uint32_t cnt_mask = 0xFFFFFFFF >> (32 - bits);
	buffer[*offset] = sample;
	*offset += 1;
	*offset &= cnt_mask;
}




void Set_Cutoff_Frequency(float sample_frequent, float cutoff_frequent,Butter_Parameter *LPF)
{
  float fr = sample_frequent / cutoff_frequent;
  float ohm = tanf(3.141592653589793f / fr);
  float c = 1.0f + 2.0f * cosf(3.141592653589793f / 4.0f) * ohm + ohm * ohm;
  if (cutoff_frequent <= 0.0f) {
    // no filtering
    return;
  }
  LPF->b[0] = ohm * ohm / c;
  LPF->b[1] = 2.0f * LPF->b[0];
  LPF->b[2] = LPF->b[0];
  LPF->a[0]=1.0f;
  LPF->a[1] = 2.0f * (ohm * ohm - 1.0f) / c;
  LPF->a[2] = (1.0f - 2.0f * cosf(3.141592653589793f / 4.0f) * ohm + ohm * ohm) / c;
}


/*************************************************
函数名:	float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
说明:	加速度计低通滤波器
入口:	float curr_input 当前输入加速度计,滤波器参数，滤波器缓存
出口:	无
备注:	2阶Butterworth低通滤波器
*************************************************/
float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
{
  /* 加速度计Butterworth滤波 */
  /* 获取最新x(n) */
  Buffer->Input_Butter[2]=curr_input;
  /* Butterworth滤波 */
  Buffer->Output_Butter[2]=
    Parameter->b[0] * Buffer->Input_Butter[2]
      +Parameter->b[1] * Buffer->Input_Butter[1]
        +Parameter->b[2] * Buffer->Input_Butter[0]
          -Parameter->a[1] * Buffer->Output_Butter[1]
            -Parameter->a[2] * Buffer->Output_Butter[0];
  /* x(n) 序列保存 */
  Buffer->Input_Butter[0]=Buffer->Input_Butter[1];
  Buffer->Input_Butter[1]=Buffer->Input_Butter[2];
  /* y(n) 序列保存 */
  Buffer->Output_Butter[0]=Buffer->Output_Butter[1];
  Buffer->Output_Butter[1]=Buffer->Output_Butter[2];
  return Buffer->Output_Butter[2];
}
