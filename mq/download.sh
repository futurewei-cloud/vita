echo " --- downloading kafka ---"
wget https://archive.apache.org/dist/kafka/2.6.0/kafka_2.13-2.6.0.tgz &&\
tar -xvf kafka_2.13-2.6.0.tgz

echo " --- downloading rabbitmq ---"
wget http://erlang.org/download/otp_src_18.2.1.tar.gz &&\
tar xvfz otp_src_18.2.1.tar.gz &&\
./configure &&\
make install

wget http://www.rabbitmq.com/releases/rabbitmq-server/v3.8.19/rabbitmq-server-generic-unix-3.8.19.tar.xz
tar -xvfz rabbitmq-server-generic-unix-3.8.19.tar

echo " --- downloading pulsar ---"
wget https://archive.apache.org/dist/pulsar/pulsar-2.6.0/apache-pulsar-2.6.0-bin.tar.gz
tar xvfz apache-pulsar-2.6.0-bin.tar.gz