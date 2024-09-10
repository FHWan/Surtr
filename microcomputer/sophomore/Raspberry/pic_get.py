import socket, time, struct, os, threading 
host = '0.0.0.0'
port = 8000 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # 定义socket类型 
s.bind((host, port)) # 绑定需要监听的Ip和端口号，tuple格式 
s.listen(5) 

def conn_thread(connection, address):
    i = 0
    while True:
        try:
            connection.settimeout(600)
            fileinfo_size = struct.calcsize('128sl')
            buf = connection.recv(fileinfo_size)
            if buf:
                filename, filesize = struct.unpack('128sl', buf)
                print("照片大小:"+str(filesize))
                if filesize< 0 or filesize > 2432075:
                    continue
                filename = filename.decode().strip('\00')
                print('file new name is %s, filesize is %s' % (filename, filesize))
                # 构造文件路径
                filepath = '/home/aed/pic/'+ filename
                file = open(filepath,'wb')
                print('stat receiving...filesize:' + str(filesize))
                recvd_size = 0 # 定义接收了的文件大小
                while recvd_size != filesize:
                    if filesize - recvd_size >= 1024:
                        rdata = connection.recv(1024)
                        recvd_size += len(rdata)
                    elif filesize - recvd_size <1024 and filesize - recvd_size > 0:
                        print(filesize - recvd_size)
                        rdata = connection.recv(filesize - recvd_size)
                        recvd_size += len(rdata)
                    file.write(rdata)
                file.close()
                print('receive done')
                # connection.close()
            i += 1
        except socket.timeout:
            connection.close()
            con.close() 
def main():
    while True:
        print("开始接收图片")
        connection, address = s.accept()
        print('Connected by ', address)
        thread = threading.Thread(target=conn_thread, args=(connection, address)) 
        thread.start()
    s.close() 

if __name__ == '__main__':
    main()
