////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for any
//    purpose with or without fee is hereby granted, provided that the above
//    copyright notice and this permission notice appear in all copies.
//
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
//    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
//    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
//    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
//    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
//    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
//    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#import "CDMUtil.h"

@interface CDMUtil()

@end

@implementation CDMUtil

+ (NSString *)convertConstCharToNSString:(const char *)constchar
{
    if ((constchar == NULL) || (constchar[0] == 0)) {
        return @"";
    }
    else {
        return(@(constchar));
    }
}

+(void) removeCellInset:(UITableViewCell *)cell
{
    if([cell respondsToSelector:@selector(preservesSuperviewLayoutMargins)]) {
        cell.layoutMargins = UIEdgeInsetsZero;
        cell.preservesSuperviewLayoutMargins = false;
    }
}

+ (UINavigationController *)getNavigationController
{
    return (UINavigationController *)[[[UIApplication sharedApplication] windows]objectAtIndex:0].rootViewController;
}

+ (NSString *)boolToNSString:(bool)boolean
{
    if(boolean){
        return @"True";
    }
    return @"False";
}

@end