//
//  UILabel+changeSpace.m
//  ONTO
//
//  Created by Apple on 2018/9/6.
//  Copyright © 2018年 Zeus. All rights reserved.
//

#import "UILabel+changeSpace.h"

@implementation UILabel (changeSpace)
/**  改变字间距和行间距  */
-(void)changeSpace:(CGFloat)lineSpace wordSpace:(CGFloat)wordSpace{
    if (self.text == nil || [self.text isEqualToString: @""]) {
        return;
    }
    
    NSString* str = self.text;
    NSMutableAttributedString * attributedString = [[NSMutableAttributedString alloc]initWithString:str attributes:@{NSKernAttributeName : @(wordSpace)}];
    NSMutableParagraphStyle *paragraphStyle = [NSMutableParagraphStyle new];
    paragraphStyle.lineSpacing  = lineSpace;
    [attributedString addAttributes:@{NSParagraphStyleAttributeName : paragraphStyle} range:NSMakeRange(0, str.length)];
    self.attributedText = attributedString;
}
@end
