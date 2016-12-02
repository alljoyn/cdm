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

#import <Foundation/Foundation.h>
#import "InterfaceViewController.h"
#import "ReadOnlyValuePropertyCell.h"
#import "ReadWriteValuePropertyCell.h"
#import "MethodViewCell.h"
#import "MethodViewOutputCell.h"
#import "SelectableValuePropertyCell.h"
#import "CDMUtil.h"

@interface InterfaceViewController()
@end

@implementation InterfaceViewController

- (id)init
{
    self = [super init];
    if (self) {
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    CGRect tableViewFrame = self.view.bounds;
    self.tableView = [[UITableView alloc]initWithFrame:tableViewFrame style:UITableViewStylePlain];
    
    [self.tableView registerClass:[ReadOnlyValuePropertyCell class] forCellReuseIdentifier:READ_ONLY_TABLE_VIEW_CELL];
    [self.tableView registerClass:[ReadWriteValuePropertyCell class] forCellReuseIdentifier:READ_WRITE_TABLE_VIEW_CELL];
    [self.tableView registerClass:[MethodViewCell class] forCellReuseIdentifier:METHOD_VIEW_TABLE_VIEW_CELL];
    [self.tableView registerClass:[MethodViewOutputCell class] forCellReuseIdentifier:METHOD_VIEW_OUTPUT_TABLE_VIEW_CELL];
    [self.tableView registerClass:[SelectableValuePropertyCell class] forCellReuseIdentifier:SELECTABLE_TABLE_VIEW_CELL];
    
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    
    self.tableView.allowsSelection = NO;
    
    [self.tableView setSeparatorInset:UIEdgeInsetsZero];
    
    [self.view addSubview:self.tableView];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    switch (section) {
        case SECTION_PROPERTY:
            return @"Properties";
        case SECTION_METHOD:
            return @"Methods";
        case SECTION_METHOD_OUTPUT:
            return @"Output";
        default:
            return @"Unknown";
    }
}

-(CGFloat) tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    switch (indexPath.section) {
        case SECTION_PROPERTY:
            return PROPERTY_CELL_HEIGHT;
            break;
        case SECTION_METHOD:
            return METHOD_CELL_HEIGHT;
            break;
        case SECTION_METHOD_OUTPUT:
            return METHOD_OUTPUT_CELL_HEIGHT;
            break;
        default:
            return DEFAULT_CELL_HEIGHT;
            break;
    }
}

@end