#include "NetworkFactory.h"
#include "include\NetworkFactory.h"

using namespace Networking;

ConnectionResolver& Networking::NetworkFactory::BuildResolver()
{
	IOServiceHandler::IncrementUserCount();
	ConnectionResolver resolver(*(IOServiceHandler::getIOService()));

	return std::move(resolver);
}

ServerListener& Networking::NetworkFactory::BuildListener()
{
	IOServiceHandler::IncrementUserCount();
	ServerListener serverListener(*(IOServiceHandler::getIOService()));

	return std::move(serverListener);
}

void Networking::NetworkFactory::Dispose(Connection * connection)
{
	if (connection == NULL)
		return;

	delete connection;
	connection = NULL;
	IOServiceHandler::DecrementUserCount();
}


void Networking::NetworkFactory::Dispose(ConnectionResolver * resolver)
{
	if (resolver == NULL)
		return;

	delete resolver;
	resolver = NULL;
	IOServiceHandler::DecrementUserCount();
}

void Networking::NetworkFactory::Dispose(ServerListener* listener)
{
	if (listener == NULL)
		return;

	delete listener;
	listener = NULL;
	IOServiceHandler::DecrementUserCount();
}

Connection& Networking::NetworkFactory::BuildConnection(tcp::socket* socket)
{
	IOServiceHandler::IncrementUserCount();
	Connection connection(socket);
	return std::move(connection);
}

std::shared_ptr<asio::io_service> Networking::NetworkFactory::IOServiceHandler::getIOService()
{
	if (aios == NULL) {
		aios = std::make_shared<asio::io_service>();
	}

	if (aiosThread != NULL) {
		StartIOThread();
	}

	return aios;
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
		aiosThread = new std::thread([]() {
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

int Networking::NetworkFactory::IOServiceHandler::userCount = 0;
