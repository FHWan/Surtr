#include <comm_CIF_COM.h>
#ifdef ROS
#include <ros/ros.h>
#endif
using namespace std;

CommCIFCOM::CommCIFCOM(void)
{
    m_COM_fd = -1;
    f_COM_disconnect = false;
}
CommCIFCOM::~CommCIFCOM()
{
  COMClose();
}
/*------------------------------------------------------------------------------------------------------------------
 * name: COMIsOpen
 * detail: Return COM state
 -----------------------------------------------------------------------------------------------------------------*/
bool CommCIFCOM::COMIsOpen()
{
    return m_COM_fd < 0 ? false : true;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: COMOpen
 * detail: Open COM with the sequence
 -----------------------------------------------------------------------------------------------------------------*/
bool CommCIFCOM::COMOpen()
{
    int count = sizeof (arr_device)/sizeof (arr_device[0]);
    if (COMIsOpen()==true)return false;
    for(int i=0;i<count;i++)
    {      
        m_COM_fd = open(arr_device[i].data(),O_RDWR | O_NOCTTY | O_NONBLOCK);
        if(m_COM_fd!=-1)
        {
            #ifdef ROS
            ROS_INFO("xnode_comm: COM device %s",arr_device[i].data());
            #else
            printf("COM device : %s",arr_device[i].data());
            #endif
            return true;
        }
    }
    #ifdef ROS
    ROS_ERROR("xnode_comm: Open COM failed");
    #else
    printf("Open COM failed");
    #endif
    return false;
}

/*------------------------------------------------------------------------------------------------------------------
 * name: COMClose
 * detail: Close COM device
 -----------------------------------------------------------------------------------------------------------------*/
void CommCIFCOM::COMClose()
{
    if(m_COM_fd < 0)return;
    close(m_COM_fd);
    m_COM_fd = -1;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: COMSet
 * detail: Set COM parameter
 -----------------------------------------------------------------------------------------------------------------*/
bool CommCIFCOM::COMSet(int baudrate, int flow_ctrl, int databits, int stopbits, int parity)
{
    if (COMIsOpen() == false)
        return false;
    struct termios options;
    if (tcgetattr(m_COM_fd, &options) != 0)
    {
        #ifdef ROS
        ROS_ERROR("xnode_comm: COM options failed");
        #else
        printf("COM options failed");
        #endif
        return (false);
    }
    ///////////////baudrate set//////////////////////////////////////
    for (int i = 0; i < sizeof(arr_baud) / sizeof(int); i++)
    {
        if (baudrate == arr_baud[i])
        {
            cfsetispeed(&options, arr_baud_set[i]);
            cfsetospeed(&options, arr_baud_set[i]);
            break;
        }
    }
    //修改控制模式，保证程序不会占用串口
    options.c_cflag |= CLOCAL;
    //修改控制模式，使得能够从串口中读取输入数据
    options.c_cflag |= CREAD;
    // 解决二进制传输时，数据遇到0x0d , 0x11,0x13 会被丢掉的问题
    options.c_iflag &= ~(BRKINT | ICRNL | ISTRIP | IXON);
    ///////////////flow ctrl set//////////////////////////////////////
    switch (flow_ctrl)
    {
    case 0: //no ctrl
        options.c_cflag &= ~CRTSCTS;
        break;
    case 1: //hardware ctrl
        options.c_cflag |= CRTSCTS;
        break;
    case 2: //software ctrl
        options.c_cflag |= IXON | IXOFF | IXANY;
        break;
    }
    //////////databits set////////////////////////////////////////////
    options.c_cflag &= ~CSIZE;
    switch (databits)
    {
    case 5:
        options.c_cflag |= CS5;
        break;
    case 6:
        options.c_cflag |= CS6;
        break;
    case 7:
        options.c_cflag |= CS7;
        break;
    case 8:
        options.c_cflag |= CS8;
        break;
    default:
        #ifdef ROS
        ROS_ERROR("xnode_comm: Wrong databits");
        #else
        printf("Wrong databits");
        #endif
        return (false);
    }
    ////////////////parity set//////////////////////////////////////
    switch (parity)
    {
    case 'n':
    case 'N': //无奇偶校验位。
        options.c_cflag &= ~PARENB;
        options.c_iflag &= ~INPCK;
        break;
    case 'o':
    case 'O': //设置为奇校验
        options.c_cflag |= (PARODD | PARENB);
        options.c_iflag |= INPCK;
        break;
    case 'e':
    case 'E': //设置为偶校验
        options.c_cflag |= PARENB;
        options.c_cflag &= ~PARODD;
        options.c_iflag |= INPCK;
        break;
    case 's':
    case 'S': //设置为空格
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        break;
    default:
        #ifdef ROS
        ROS_ERROR("xnode_comm: Wrong parity");
        #else
        printf("Wrong parity");
        #endif
        return (false);
    }
    ////////////////stopbits set//////////////////////////////////////
    switch (stopbits)
    {
    case 1:
        options.c_cflag &= ~CSTOPB;
        break;
    case 2:
        options.c_cflag |= CSTOPB;
        break;
    default:
        #ifdef ROS
        ROS_ERROR("xnode_comm: Wrong stopbits");
        #else
        printf("Wrong stopbits");
        #endif
        return (false);
    }

    //修改输出模式，原始数据输出
    options.c_oflag &= ~OPOST;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    //设置等待时间和最小接收字符
    options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */
    options.c_cc[VMIN] = 1;  /* 读取字符的最少个数为1 */

    //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读
    tcflush(m_COM_fd, TCIFLUSH);

    //激活配置 (将修改后的termios数据设置到串口中）
    if (tcsetattr(m_COM_fd, TCSANOW, &options) != 0)
    {
        #ifdef ROS
        ROS_ERROR("xnode_comm: options set failed");
        #else
        printf("options set failed");
        #endif
        return (false);
    }
    return (true);
}
/*------------------------------------------------------------------------------------------------------------------
 * name: COMInitDefault
 * detail: Open and set COM default parameter
 -----------------------------------------------------------------------------------------------------------------*/
bool CommCIFCOM::COMInitDefault()
{
    if(COMOpen() == false)return false;
    if(COMSet(460800,0,8,1,'n') == false)return false;
    tcflush(m_COM_fd, TCIOFLUSH); //flush IO quene
    return true;
}
/*------------------------------------------------------------------------------------------------------------------
 * name: COMDataSend
 * detail: As name.
 -----------------------------------------------------------------------------------------------------------------*/
unsigned long CommCIFCOM::COMDataSend(vector<unsigned char> data)
{
    static int disconnect_count = 0;
    if (COMIsOpen()==false)return false;
    unsigned long data_len = data.size();
    unsigned long len = 0;
    if(data_len == 0)return false;
    while(1)
    {
        len = write(m_COM_fd, &data[0], data_len);

        if (len == data_len)
        {
            disconnect_count = 0;
            return len;
        }
        //COM send error
        if(len == -1)
        {
            disconnect_count++;
            //disconnect handle
            if(disconnect_count == 200)
            {
                disconnect_count = 0;
                f_COM_disconnect = true;
                #ifdef ROS
                ROS_ERROR("xnode_comm: COM diconnect");
                #else
                printf("COM diconnect");
                #endif
                COMClose();
                return false;
            }
            continue;
        }
        //not send all data
        #ifdef ROS
        ROS_ERROR("xnode_comm: COM lost send data");
        #else
        printf("COM lost send data");
        #endif
        return len;
    }
}
/*------------------------------------------------------------------------------------------------------------------
 * name: DataRecv
 * detail: As name.
 -----------------------------------------------------------------------------------------------------------------*/
vector<unsigned char> CommCIFCOM::COMDataRecv(void)
{
    static int disconnect_count = 0;
    fd_set fs_read;
    vector<unsigned char> recv_buff;
    unsigned char buff[100] = {0};
    struct timeval time;
    time.tv_sec = 0;
    time.tv_usec = 1000;
    int len, fs_sel;
    unsigned long pos =0;

    recv_buff.clear();
    if (COMIsOpen()==false)return recv_buff;

    while(1)
    {
        FD_ZERO(&fs_read);
        FD_SET(m_COM_fd, &fs_read);
        fs_sel = select(m_COM_fd + 1, &fs_read, NULL, NULL, &time);//使用select实现串口的多路通信

        if (fs_sel > 0)
        {
            len = read(m_COM_fd, buff , 100);
            //available data
            if(len > 0)
            {
                disconnect_count = 0;
                for(int i=0;i<len;i++)
                {
                  recv_buff.push_back(buff[i]);
                }
                //too long data
                if(recv_buff.size()>2048)return recv_buff;
                continue;
            }
            //COM error
            if(len == -1)
            {
                #ifdef ROS
                ROS_ERROR("xnode_comm: COM read error");
                #else
                printf("COM read error");
                #endif
                disconnect_count++;
                //lost connect handle
                if(disconnect_count == 200)
                {
                    disconnect_count = 0;
                    f_COM_disconnect = true;
                    #ifdef ROS
                    ROS_ERROR("xnode_comm: COM diconnect");
                    #else
                    printf("COM diconnect");
                    #endif
                    COMClose();
                    return recv_buff;
                }
                continue;
            }
            //no more data
            disconnect_count = 0;
            return recv_buff;
        }
        else
            return recv_buff;
    }
}
/*------------------------------------------------------------------------------------------------------------------
 * name: DataClear
 * detail: As name.
 -----------------------------------------------------------------------------------------------------------------*/
void CommCIFCOM::DataClear()
{
    if (COMIsOpen()==false)return;
    tcflush(m_COM_fd, TCIOFLUSH);
}

