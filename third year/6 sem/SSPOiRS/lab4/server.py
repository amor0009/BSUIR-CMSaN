import socket
import os
import fcntl
import select

BIND_ADDRESS = "172.20.10.5"
BIND_PORT = 54321
FRAME_SIZE = 1024

SIGTERM = 15

PROC_NMIN = 2
PROC_NMAX = 5
WORKER_TIMEOUT = 10


def createWorker(serverSocket, timeout):
    readfd, writefd = os.pipe()
    makeFDInheritable(writefd)
    pid = os.fork()
    if pid == 0:
        os.execv('/home/amor/SSPOiRS/lab4/.venv/bin/python',
                 ['python', os.path.realpath("./server_worker.py"), str(serverSocket.fileno()), str(timeout),
                  str(writefd)])

    global workerCount
    workerCount += 1
    workersPID.append(pid)
    workerPipes.append(readfd)

    return pid


def destroyWorker(pid):
    os.kill(pid, SIGTERM)

    del workerPipes[(workersPID.index(pid))]
    workersPID.remove(pid)
    global workerCount
    workerCount -= 1


def initProcessPool(serverSocket):
    for i in range(PROC_NMIN):
        createWorker(serverSocket, WORKER_TIMEOUT)

    print(f"Пул процессов инициализирован {workerCount} процессами")
    print(f"Process IDs: {workersPID}\n")


def destroyProcessPool():
    for pid in workersPID:
        destroyWorker(pid)
    for pipe in workerPipes:
        os.close(pipe)


def printWorkersInfo():
    print(f"Текущее кол-во процессов: {workerCount}")
    print(f"Process IDs: {workersPID}\n")


def addDynamicWorker(serverSocket):
    pid = createWorker(serverSocket, WORKER_TIMEOUT)
    global skipSelect
    skipSelect = True
    print(f"Выделен новый процесс (PID: {pid})")
    printWorkersInfo()


def removeDynamicWorker(pid):
    destroyWorker(pid)
    print(f"Процесс (PID: {pid}) уничтожен по причине неактивности.")
    printWorkersInfo()


def setOptions(serverSocket):
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    return serverSocket


def makeFDInheritable(fd):
    flags = fcntl.fcntl(fd, fcntl.F_GETFD)
    fcntl.fcntl(fd, fcntl.F_SETFD, flags & ~fcntl.FD_CLOEXEC)


def handleWorkerTimeout(pid):
    if workerCount > PROC_NMIN:
        removeDynamicWorker(pid)


# ------------

try:
    workerCount = 0
    connCount = 0
    workersPID = []
    workerPipes = []

    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket = setOptions(serverSocket)
    serverSocket.bind((BIND_ADDRESS, BIND_PORT))
    serverSocket.listen()

    makeFDInheritable(serverSocket.fileno())

    print("\nСервер начал работу.\n")

    initProcessPool(serverSocket)

    while True:
        pipesToRead, _, _ = select.select(workerPipes, [], [], 0.1)
        for pipe in pipesToRead:
            status = os.read(pipe, 1).decode()
            if status == "A":
                connCount += 1
                print(f"Всего подключений {connCount}\n")
            if status == "F":
                connCount -= 1
                print(f"Всего подключений {connCount}\n")
            if status == "T":
                handleWorkerTimeout(workersPID[workerPipes.index(pipe)])

        if workerCount >= PROC_NMIN and workerCount < PROC_NMAX and workerCount == connCount:
            newConn, _, _ = select.select([serverSocket], [], [], 0.1)
            if newConn:
                addDynamicWorker(serverSocket)

except KeyboardInterrupt:
    print("\nЗавершение работы.\n")
finally:
    destroyProcessPool()