//
//  ChatContainerViewController.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-21.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit

class ChatContainerViewController: UIViewController
{
    var senderDisplayName = String()
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        super.prepare(for: segue, sender: sender)
        let chatViewController = segue.destination as! ChatViewController
        
        chatViewController.senderDisplayName = senderDisplayName
    }
}
