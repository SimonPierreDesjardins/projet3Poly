//
//  Lock.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-06.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import Foundation

func lock(lock: AnyObject, execute: () -> ())
{
    objc_sync_enter(lock)
    execute()
    objc_sync_exit(lock)
}
