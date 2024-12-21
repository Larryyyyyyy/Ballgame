#include "client.h"
client::client() {
    socket.setBlocking(false);//½ûÖ¹×èÈû
}
void client::connectToServer(string ipAddress, int port) {
    if (socket.connect(ipAddress, port) != Socket::Done) {
        cerr << "Failed to connect to server\n";
    }
    cout << "Connected to server\n";
}
void client::sendMessage(float px, float py, bool leftClicked, bool playWay, bool isCuePressed, float magnitude, float angle, int version, vector<Ball> balls) {
    packet << px << py << leftClicked << magnitude << angle << playWay << isCuePressed << version;
    for (int i = 0; i < balls.size(); ++i) {
        packet << balls[i].shape.getPosition().x << balls[i].shape.getPosition().y;
    }
    socket.send(packet);
    packet.clear();
}
void client::receiveMessage(float& px, float& py, bool& leftClicked, bool& playWay, bool& isCuePressed, float& magnitude, float& angle, int& version, vector<Ball>& balls) {
    float posx = 0, posy = 0;
    Socket::Status status = socket.receive(packet);
    if (status == sf::Socket::Done) {
        packet >> px >> py >> leftClicked >> magnitude >> angle >> playWay >> isCuePressed >> version;
        for (int i = 0; i < balls.size(); ++i) {
            packet >> posx >> posy;
            balls[i].shape.setPosition(posx, posy);
        }
        packet.clear();
    }
    else if (status == Socket::NotReady) {
        cerr << "Socket not ready to receive data" << endl;
    }
    else {
        cerr << "Failed to receive data: " << status << endl;
    }
}
