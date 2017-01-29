//
//  ChatCell.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-17.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit
import JSQMessagesViewController

class CustomMessagesCollectionViewCellIncoming: CustomMessagesCollectionViewCell {
    
    override func awakeFromNib() {
        super.awakeFromNib()
        self.messageBubbleTopLabel.textAlignment = NSTextAlignment.right
        self.cellBottomLabel.textAlignment = NSTextAlignment.right
    }

    override class func nib() -> UINib {
        return UINib (nibName: "CustomMessagesCollectionViewCellIncoming", bundle: nil)
    }
    
    override class func cellReuseIdentifier() -> String {
        return "CustomMessagesCollectionViewCellIncoming"
    }
    
    override class func mediaCellReuseIdentifier() -> String {
        return "CustomMessagesCollectionViewCellIncoming_JSQMedia"
    }
}
