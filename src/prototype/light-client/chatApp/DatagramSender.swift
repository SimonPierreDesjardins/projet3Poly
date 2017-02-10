//
//  SocketIOManager.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-01.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import SwiftSocket

class DatagramSender
{
    private var client: TCPClient?
    var isListening: Bool
    
    init()
    {
        isListening = false
    }
    
    func establishConnection(ipAdress: String, port: Int) -> Bool
    {
        client = TCPClient(address: ipAdress, port: Int32(port))
        switch client!.connect(timeout: 5) {
            case .success:
                print("yay")
                listenToMessages()
                return true
            case .failure(let error):
                print(error)
                return false
        }
    }
    
    func sendMessage(_ message: String)
    {
        let bytesSize = [UInt8](message.utf8).count
        let datagram = String(bytesSize) + ";" + message
        switch client!.send(string: datagram) {
            case .success:
                break

            case .failure:
                NotificationCenter.default.post(name: .Datagram_onServerDoesNotRespond, object: nil)
        }
    }
    
    func listenToMessages()
    {
        let concurrentQueue = DispatchQueue(label: "queuename", qos: .utility, attributes: .concurrent)
        concurrentQueue.async {
            
        }
        DispatchQueue.global(qos: .utility).async
        {
            lock(lock: self.isListening as AnyObject, execute: { self.isListening = true })
            while self.isListening
            {
                guard let data = self.client!.read(1024*10) else { return }
                if !data.isEmpty
                {
                    DispatchQueue.main.async {
                        NotificationCenter.default.post(name: .Datagram_chatDatagramReceived, object: nil, userInfo: ["data" : data])
                    }
                }
            }
        }
    }
    
    func poll()
    {
        DispatchQueue.global(qos: .utility).async
        {
            lock(lock: self.isListening as AnyObject, execute: { self.isListening = true })
            while self.isListening
            {
                guard let data = self.client!.read(1024*10) else { return }
                let datagram = String(bytes: data, encoding: .utf8)
                if datagram != nil
                {
                    DispatchQueue.main.async {
                        NotificationCenter.default.post(name: .Datagram_chatDatagramReceived, object: nil, userInfo: ["datagram" : datagram!])
                    }
                }
            }
        }
    }
    
    func stopListeningToMessages()
    {
        lock(lock: self.isListening as AnyObject, execute: { self.isListening = false })
    }
    
    func closeConnection()
    {
        stopListeningToMessages()
        client!.close()
    }
}
