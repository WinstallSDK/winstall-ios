//
//  WinstallSDK.h
//  WinstallSDK
//
//  Created by WinstallSDK on 2020/6/10.
//  Copyright © 2020 chen. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol WinInstallDelegate<NSObject>

/**
 * 唤醒时获取h5页面动态参数（如果是渠道链接，渠道编号会一起返回）
 * @param params 动态参数对象
 */
- (void)getWakeUpParams:(id _Nullable ) params;

@end

@interface WinstallSDK : NSObject

/**
 * SDK单例,returns a previously instantiated singleton instance of the API.
 */
+(instancetype _Nullable)defaultManager;

/**
 * 开发者在需要获取用户安装app后由web网页传递过来的”动态参数“（如邀请码、游戏房间号，渠道编号等）时调用该方法,可第一时间返回数据，可在任意位置调用
 *
 * 默认回调超时时长由10秒(s)，如无特殊需求，请用此方法，否则可使用高级API
 *
 * @param completedBlock 回调block，在主线程（UI线程）回调
 *
 * @discussion
 1、不要自己保存动态安装参数，在每次需要用到参数时，请调用该方法去获取；
 2、该方法默认超时为8秒，尽量写在业务场景需要参数的位置调用（在业务场景时，网络一般都是畅通的），例如，可以选择在用户注册成功后调用该方法获取参数，对用户进行奖励。原因是iOS首次安装、首次启动的app，会询问用户获取网络权限，用户允许后SDK才能正常联网去获取参数。如果调用过早，可能导致网络权限还未允许就被调用，导致参数无法及时拿到，误以为参数不存在（此时getInstallParmsCompleted法已超时，回调返回空）；
 3. 如果是业务需要，必须在application:didFinishLaunchingWithOptions方法中获取参数，可调用下面高级API，修改超时时长，比如15秒或更长，如果只是拿参数在后台“悄悄地”进行数据统计的情况，超时时长设置为半个小时或更长都是ok的，根据需要来。
 
 * ***该方法可重复获取参数
 */
-(void)getInstallParmsCompleted:(void (^_Nullable)(id _Nullable params))completedBlock;


/**
* 开发者在需要获取用户安装app后由web网页传递过来的”动态参数“（如邀请码、游戏房间号，渠道编号等）时调用该方法,可第一时间返回数据，可在任意位置调用
*
* @param timeoutInterval 可设置回调超时时长，单位秒(s)
* @param completedBlock 回调block，在主线程（UI线程）回调
*
* @discussion
* ***开发者不要自行保存参数!!!如果获取动态参数成功，SDK会把参数保存在本地***
* ***该方法可重复获取参数
*/
-(void)getInstallParmsWithTimeoutInterval:(NSTimeInterval)timeoutInterval completed:(void (^_Nullable)(id _Nullable params))completedBlock;


/**
 * 初始化WinstallSDK
 * ***调用该方法前，需在Info.plist文件中配置键值对,键为com.winstallSDK.APP_KEY不能修改，值为相应的应用的appKey，可在WinstallSDK官方后台查看***
 
 <key>com.winstallSDK.APP_KEY</key>
 <string>你的appKey</string>
 
 * @param delegate 委托方法所在的类的对象
 */
+(void)initWithDelegate:(id<WinInstallDelegate> _Nonnull)delegate;


/**
 * 初始化WinstallSDK (请参考方法 initwithDelegate: 已使用该初始化方法的用户也可继续使用)
 *
 * @param appKey 控制中心创建应用获取appKey
 * @param delegate 委托方法(getWakeUpParams)所在的类的对象
 */
+(void)setAppKey:(nonnull NSString *)appKey withDelegate:(nullable id<WinInstallDelegate>)delegate;


@end
