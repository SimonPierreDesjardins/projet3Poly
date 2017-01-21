//
//  MessageViewIncoming.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-21.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit
import JSQMessagesViewController

class MessageViewOutgoing: JSQMessagesCollectionViewCellOutgoing {
    @IBOutlet weak var timeLabel: UILabel!
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    override class func nib() -> UINib {
        return UINib (nibName: "MessageViewOutgoing", bundle: Bundle.main)
    }
    
    override class func cellReuseIdentifier() -> String {
        return "MessageViewOutgoing"
    }
    
    override class func mediaCellReuseIdentifier() -> String {
        return "MessageViewOutgoing_JSQMedia"
    }
    
}
