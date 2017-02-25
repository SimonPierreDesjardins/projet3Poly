#include "NetworkFactory.h"
#include "include\NetworkFactory.h"

using namespace Networking;

ConnectionResolver* Networking::NetworkFactory::BuildResolver()
{
	iosHandler.IncrementUserCount();
	ConnectionResolver* resolver = new ConnectionResolver(*(iosHandler.getIOService()));

	return std::move(resolver);
}

ServerListener* Networking::NetworkFactory::BuildListener(short port)
{
	iosHandler.IncrementUserCount();
	ServerListener* serverListener = new ServerListener(*(iosHandler.getIOService()), port);

	return std::move(serverListener);
}

Connection* Networking::NetworkFactory::BuildConnection(tcp::socket* socket)
{
	iosHandler.IncrementUserCount();
	return std::move(new Connection(socket));
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
	_threadLock.lock();
	if (aiosThread == NULL) {
		aiosThread = new std::thread([this]() {
			// keep running as long as there are users of the IOThread.
			while (userCount > 0 ) {
				aios->run();
			}
		});
	}
	_threadLock.unlock();
}

void Networking::NetworkFactory::IOServiceHandler::StopIOThread()
{
	_threadLock.lock();

	if (aiosThread != NULL && aios != NULL) {
		// Stop service and thread
		aios->stop();
		while (!(aiosThread->joinable()));
		aiosThread->join();

		// Clean pointer
		delete aiosThread;
		aiosThread = NULL;
	}

	_threadLock.unlock();
}

Networking::NetworkFactory::IOServiceHandler Networking::NetworkFactory::iosHandler;