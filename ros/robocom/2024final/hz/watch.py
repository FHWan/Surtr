import subprocess

def start_python_scripts(scripts):
    processes = []
    for script in scripts:
        # 启动每个 Python 脚本
        process = subprocess.Popen(['python', script])
        processes.append(process)
    
    # 等待所有子进程完成
    for process in processes:
        process.wait()

if __name__ == '__main__':
    # 提供 Python 文件的完整路径
    scripts = ['hz_1.py', 'hz_2.py', '/home/eaibot/2024final/rq/rq.py']
    print("OK")
    start_python_scripts(scripts)

