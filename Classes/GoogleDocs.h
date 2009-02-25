//
//  GoogleDocs.h
//  GoogleDocs
//
//  Created by Tom Saxton on 12/19/08.
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

#import <Foundation/Foundation.h>

@class GDataFeedDocList, GDataServiceTicket, GDataServiceTicket, GoogleDocs;

// Error codes defined and generated by the GoogleDocs class, not part of the GDataAPI
// These will be embedded in NSError records returned through the various completion callbacks
typedef enum
{
	gecResursion = 50,
	gecMissingFolderFeed,
	gecFolderNotFound,
	gecUnknownFileExtension,
	gecNewFolderCreationError,
	gecFetcherInitFailed,
} GEC;

@protocol GoogleDocsController

- (void)googleDocsAccountVerifyComplete:(GoogleDocs *)googledocs valid:(BOOL)fValid error:(NSError *)error;

- (void)googleDocsUploadProgress:(GoogleDocs *)googledocs read:(unsigned long long)cbRead of:(unsigned long long)cbTotal;
- (void)googleDocsUploadComplete:(GoogleDocs *)googledocs error:(NSError *)error;

- (void)googleDocsDownloadProgress:(GoogleDocs *)googledocs read:(unsigned long long)cbReadSoFar;
- (void)googleDocsDownloadComplete:(GoogleDocs *)googledocs data:(NSData *)data error:(NSError *)error;

- (void)googleDocsRetitleComplete:(GoogleDocs *)googledocs success:(BOOL)fSuccess count:(NSInteger)count error:(NSError*)error;

- (void)googleDocsDeleteComplete:(GoogleDocs *)googledocs success:(BOOL)fSuccess count:(NSInteger)count error:(NSError*)error;

- (void)googleDocsCheckFolderComplete:(GoogleDocs *)googledocs exists:(BOOL)fExists wasCreated:(BOOL)fCreated error:(NSError *)error;

@end


@interface GoogleDocs : NSObject
{
@private
	NSObject <GoogleDocsController> *m_owner;
	NSString *m_username;
	NSString *m_password;
	
	GDataFeedDocList *m_feedDocList;
	NSError *m_errorDocListFetch;
	GDataServiceTicket *m_ticketDocListFetch;
	GDataServiceTicket *m_ticketUpload;

	// the current Google operation
	NSInteger m_gop;
	NSString *m_title;
	NSArray *m_adirPath;
	NSInteger m_idirPath;
	NSURL *m_urlFolderFeed;
	NSString *m_titleNew;
	BOOL m_fCanCreateDir;
	BOOL m_fDidCreateDir;
	
	// feed caching
	NSArray *m_adirPathCache;
	NSURL *m_urlFolderFeedCache;
	BOOL m_fUsedCache;

	// upload state
	NSData *m_dataToUpload;
	BOOL m_fReplaceExisting;
	
	// retitle file state
	NSArray *m_aentryRetitle;
	NSInteger m_ientryRetitle;

	// delete files state
	NSInteger m_cfileKeep;
	NSArray *m_aentryDelete;
	NSInteger m_ientryDelete;
}

@property (nonatomic, retain) NSString *username;
@property (nonatomic, retain) NSString *password;

- (id)initWithUsername:(NSString *)username password:(NSString *)password owner:(NSObject <GoogleDocsController> *)owner;

- (void)verifyAccountUsername:(NSString *)username password:(NSString *)password;
- (void)beginUploadData:(NSData *)dataUpload withTitle:(NSString *)title inFolder:(id)dirStringOrArray replaceExisting:(BOOL)fReplaceExisting;
- (void)beginDownloadTitle:(NSString *)title inFolder:(id)dirStringOrArray;
- (void)beginFileRetitleFrom:(NSString *)titleOld toTitle:(NSString *)titleNew inFolder:(id)dirStringOrArray;
- (void)beginFileDeleteTitle:(NSString *)title inFolder:(id)dirStringOrArray keepingNewest:(NSInteger)cfileKeep;
- (void)beginFolderCheck:(id)dirStringOrArray createIfNeeded:(BOOL)fCreate;

@end
