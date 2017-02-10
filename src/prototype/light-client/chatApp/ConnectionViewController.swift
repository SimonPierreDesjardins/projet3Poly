//
//  ConnexionController.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-20.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit

class ConnectionViewController: UIViewController, UITextFieldDelegate
{
    @IBOutlet weak var connectButton: UIButton!
    @IBOutlet weak var usernameTextBox: UITextField!
    @IBOutlet weak var bottomLayoutGuideConstraint: NSLayoutConstraint!
    @IBOutlet weak var usernameErrorLabel: UILabel!
    @IBOutlet weak var portTextBox: UITextField!
    @IBOutlet weak var ipAdressTextBox: UITextField!
    
    var isKeyboardHidingComponent = false
    var keyboardHeight = CGFloat()
    
    var usernameMaxLength: Int? = 0
    
    var textBoxesEmptyStates: [Bool] = [Bool]()
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        registerForKeyboardNotifications()
        self.usernameErrorLabel.alpha = 0.0
    }
    
    override func viewDidLoad() {
        connectButton.addTarget(self, action: #selector(self.connectButtonTapped), for: .touchUpInside)
        AppDelegate.chatDelegator.setConnectionViewController(self)
        
        usernameTextBox.delegate = self
        textBoxesEmptyStates.append(false)
        if usernameTextBox.text!.isEmpty{
            connectButton.isEnabled = false
        }
        
        ipAdressTextBox.delegate = self
        textBoxesEmptyStates.append(false)
        if ipAdressTextBox.text!.isEmpty{
            connectButton.isEnabled = false
        }
        
        portTextBox.delegate = self
        textBoxesEmptyStates.append(false)
        if portTextBox.text!.isEmpty{
            connectButton.isEnabled = false
        }
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        deregisterFromKeyboardNotifications()
    }
    
    func registerForKeyboardNotifications()
    {
        //Adding notifies on keyboard appearing
        NotificationCenter.default.addObserver(self, selector: #selector(self.keyboardWasShown), name: NSNotification.Name.UIKeyboardWillShow, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(self.keyboardWillBeHidden), name: NSNotification.Name.UIKeyboardWillHide, object: nil)
    }
    
    
    func deregisterFromKeyboardNotifications()
    {
        //Removing notifies on keyboard appearing
        NotificationCenter.default.removeObserver(self, name: NSNotification.Name.UIKeyboardWillShow, object: nil)
        NotificationCenter.default.removeObserver(self, name: NSNotification.Name.UIKeyboardWillHide, object: nil)
    }
    
    func keyboardWasShown(notification: NSNotification)
    {
        //Need to calculate keyboard exact size due to Apple suggestions
        let info : NSDictionary = notification.userInfo! as NSDictionary
        let keyboardSize = (info[UIKeyboardFrameBeginUserInfoKey] as? NSValue)?.cgRectValue.size
        keyboardHeight = keyboardSize!.height
        
        var aRect : CGRect = self.view.frame
        aRect.size.height -= keyboardSize!.height
        isKeyboardHidingComponent = !aRect.contains(connectButton!.frame.origin)
        if (isKeyboardHidingComponent)
        {
            bottomLayoutGuideConstraint.constant += keyboardHeight
        }
    }
    
    func keyboardWillBeHidden(notification: NSNotification)
    {
        if (isKeyboardHidingComponent)
        {
            bottomLayoutGuideConstraint.constant -= keyboardHeight
        }
    }
    
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        
        let textFieldText: NSString = (textField.text ?? "") as NSString
        let txtAfterUpdate = textFieldText.replacingCharacters(in: range, with: string)
        
        let isEmpty: Bool = txtAfterUpdate.isEmpty
        
        var returnCondition: Bool = true
        switch textField
        {
            case usernameTextBox:
                self.textBoxesEmptyStates[0] = isEmpty
                returnCondition = txtAfterUpdate.characters.count <= usernameMaxLength!
                break
            
            case ipAdressTextBox:
                self.textBoxesEmptyStates[1] = isEmpty
                break
    
            case portTextBox:
                self.textBoxesEmptyStates[2] = isEmpty
                break
            
            default:
                break
        }
        
        self.connectButton.isEnabled = !self.textBoxesEmptyStates.contains(true)

        return returnCondition
    }
    
    func connectButtonTapped()
    {
        self.connectButton.isEnabled = false
        hideUsernameErrorLabel()
        NotificationCenter.default.post(name: .Chat_onUsernameNeedVerification, object: nil, userInfo: ["username":usernameTextBox.text!, "ipAdress":ipAdressTextBox.text!, "port":portTextBox.text!])
    }
    
    func transitionViewToChatViewController(username: String)
    {
        let chatViewController = ChatViewController()
        chatViewController.senderId = username
        chatViewController.senderDisplayName = username
        present(chatViewController, animated: true, completion: nil)
        self.connectButton.isEnabled = true
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?)
    {
        super.prepare(for: segue, sender: sender)
        let chatViewController = segue.destination as! ChatViewController
        
        chatViewController.senderDisplayName = usernameTextBox.text!
    }
    
    func hideUsernameErrorLabel()
    {
        UIView.animate(withDuration: 0.5, delay: 0.0, options: UIViewAnimationOptions.curveEaseOut, animations: {
            self.usernameErrorLabel.alpha = 0.0
        }, completion: nil)
    }
    
    func showUsernameErrorLabel()
    {
        UIView.animate(withDuration: 0.5, delay: 0.0, options: UIViewAnimationOptions.curveEaseIn, animations: {
            self.usernameErrorLabel.alpha = 1.0
        }, completion: nil)
    }
    
    func showUsernameError(_ errorMessage: String)
    {
        hideUsernameErrorLabel()
        usernameErrorLabel.text = errorMessage
        showUsernameErrorLabel()
        self.connectButton.isEnabled = true
    }
    
    func showUsernameAlreadyUsedError()
    {
        showUsernameError("Nom d'utilisateur déjà en utilisation.")
    }
    
    func showUsernameInvalidError()
    {
        showUsernameError("Nom d'utilisateur contient des caractères invalides.")
    }
    
    func showConnectionError()
    {
        showUsernameError("Impossible de se connecter.")
    }
}

