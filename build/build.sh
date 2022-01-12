BUILD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
echo "build path is $BUILD"


docker build -f $BUILD/Dockerfile -t build0 .
docker rm -f a1 || true
docker create -v $BUILD/..:/mnt/host/code -it --privileged --cap-add=NET_ADMIN --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --name a1 build0:latest /bin/bash
docker start a1

echo "    --- running agent ---"
# sends output to null device, but stderr to console 
docker exec a1 bash -c "nohup /mnt/host/code/build/bin/Agent -d > /dev/null 2>&1 &"