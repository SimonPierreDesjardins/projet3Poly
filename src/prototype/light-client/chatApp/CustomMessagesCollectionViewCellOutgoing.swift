//
//  MessageViewIncoming.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-21.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit
import JSQMessagesViewController

class CustomMessagesCollectionViewCellOutgoing: CustomMessagesCollectionViewCell{
    override func awakeFromNib() {
        super.awakeFromNib()
        self.messageBubbleTopLabel.textAlignment = NSTextAlignment.left
        self.cellBottomLabel.textAlignment = NSTextAlignment.left
    }
   
    override class func nib() -> UINib {
        return UINib (nibName: "CustomMessagesCollectionViewCellOutgoing", bundle: nil)
    }
    
    override class func cellReuseIdentifier() -> String {
        return "CustomMessagesCollectionViewCellOutgoing"
    }
    
    override class func mediaCellReuseIdentifier() -> String {
        return "CustomMessagesCollectionViewCellOutgoing_JSQMedia"
    }
    
}
