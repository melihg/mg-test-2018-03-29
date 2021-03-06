//
//  PasswordView.h
//  GoogleDocs
//
//  Created by Tom Saxton on 12/23/08.
//  Copyright (c) 2008-2009 Idle Loop Software Design, LLC.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import <UIKit/UIKit.h>


@interface PasswordView : UIView
{
@private
	IBOutlet UITextField *m_textfieldUsername;
	IBOutlet UITextField *m_textfieldPassword;
	IBOutlet UILabel *m_labelStatus;
	IBOutlet UIActivityIndicatorView *m_spinner;
	IBOutlet UILabel *m_labelErrorMsg;
}

@property (nonatomic, assign, readonly) UITextField *textfieldUsername;
@property (nonatomic, assign, readonly) UITextField *textfieldPassword;
@property (nonatomic, assign, readonly) UILabel *labelStatus;
@property (nonatomic, assign, readonly) UILabel *labelErrorMsg;
@property (nonatomic, assign, readonly) UIActivityIndicatorView *spinner;

@end
