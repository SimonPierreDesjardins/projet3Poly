//
//  ViewController.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-17.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit
import JSQMessagesViewController


class ChatViewController: JSQMessagesViewController {
    
    
    var chatHistoric = [String]()
    
    let textCellIdentifier = "chatCell"
    
    let date = Date()
    
    let calendar = Calendar.current
    
    @IBOutlet weak var chatSendButtonHeightConstraint: NSLayoutConstraint!
    @IBOutlet weak var chatBoxHeightConstraint: NSLayoutConstraint!
    @IBOutlet weak var chatTableView: UITableView!
    @IBOutlet weak var chatBoxView: UITextView!
    @IBOutlet weak var chatSendButt: UIButton!

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.senderId = "Moi"
        
        self.senderDisplayName = "Philippe"
        
        
    }
    
    
}

