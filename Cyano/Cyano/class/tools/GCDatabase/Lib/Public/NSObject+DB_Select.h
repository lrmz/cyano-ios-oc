//
//  NSObject+DB_Select.h
//  GCDatabase
//
//  Created by Faney on 16/1/26.
//  Copyright © 2016年 Faney. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSObject (DB_Select)

+ (NSMutableArray *)selectWhereArray:(NSArray *)whereArray orderBy:(NSString *)orderBy;

@end
