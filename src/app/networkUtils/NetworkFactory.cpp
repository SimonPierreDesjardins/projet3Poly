#include "NetworkFactory.h"
#include "include\NetworkFactory.h"

using namespace Networking;

ConnectionResolver* Networking::NetworkFactory::BuildResolver()
{
	iosHandler.IncrementUserCount();
	ConnectionResolver* resolver = new ConnectionResolver(*(iosHandler.getIOService()));

	return std::move(resolver);
}

ServerListener* Networking::NetworkFactory::BuildListener()
{
	iosHandler.IncrementUserCount();
	ServerListener* serverListener = new ServerListener(*(iosHandler.getIOService()));

	return std::move(serverListener);
}

Connection& Networking::NetworkFactory::BuildConnection(tcp::socket* socket)
{
	iosHandler.IncrementUserCount();
	Connection connection(socket);
	return std::move(connection);
}

std::shared_ptr<asio::io_service> Networking::NetworkFactory::IOServiceHandler::getIOService()
{
	if (aios == NULL) {
		aios = std::make_shared<asio::io_service>();
	}

	StartIOThread();

	return aios;
}

Networking::NetworkFactory::IOServiceHandler::~IOServiceHandler()
{
	StopIOThread();
}

void Networking::NetworkFactory::IOServiceHandler::IncrementUserCount()
{
	userCount++;
}

void Networking::NetworkFactory::IOServiceHandler::DecrementUserCount()
{
	if (userCount <= 0)
		return;

	userCount--;
	if (userCount == 0) {
		StopIOThread();
	}
}

void Networking::NetworkFactory::IOServiceHandler::StartIOThread()
{
	if (aiosThread == NULL) {
		aiosThread = new std::thread([this]() {
			// keep running as long as there are users of the IOThread.
			if (aios->stopped() && userCount > 0 ) {
				aios->run();
			}
		});
	}
}

void Networking::NetworkFactory::IOServiceHandler::StopIOThread()
{
	if (aiosThread == NULL || aios == NULL)
		return;

	// Stop service and thread
	aios->stop();
	while (!(aiosThread->joinable()));
	aiosThread->join();

	// Clean pointer
	delete aiosThread;
	aiosThread = NULL;
}

Networking::NetworkFactory::IOServiceHandler Networking::NetworkFactory::iosHandler;