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
    let client = TCPClient(address: "132.207.241.132", port: 5000)
    
    func establishConnection()
    {
        switch client.connect(timeout: 1) {
            case .success:
                print("yay")
                break
            case .failure(let error):
                print(error)
        }
    }
    
    func sendMessage(_ message: String)
    {
        switch client.send(string: message) {
        case .success:
            guard let data = client.read(1024*10) else { return }
            
            if let response = String(bytes: data, encoding: .utf8)
            {
                print(response)
            }
        case .failure(let error):
            print(error)
        }
    }
    
    func listenToMessages()
    {
        DispatchQueue.global(qos: .utility).async
        {
            while true
            {
                guard let data = self.client.read(1024*10) else { return }
                let datagram = String(bytes: data, encoding: .utf8)
                if datagram != nil
                {
                    NotificationCenter.default.post(name: .Datagram_chatDatagramReceived, object: nil, userInfo: ["Datagram" : datagram!])
                }
            }
        }
    }
    
    func closeConnection()
    {
        client.close()
    }
}
