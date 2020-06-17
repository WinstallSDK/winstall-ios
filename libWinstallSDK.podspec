Pod::Spec.new do |s|
s.name                  = "libWinstallSDK"
s.version               = '1.0.0'
s.summary               = "libWinstallSDK's officially supported iOS SDK"
s.description           = <<-DESC
    libWinstallSDK's officially supported iOS SDK for pod.
DESC

s.homepage              = "https://www.winstall.cc"
s.license               = 'MIT'
s.author                = { "Cooper" => "winstall@163.com"}
s.source                = { :git => "https://github.com/WinstallSDK/winstall-ios.git", :tag => s.version.to_s }

s.vendored_libraries = 'frameworks/libWinstallSDK.a'
s.source_files = 'Classes/**/*.{h,m}'

s.platform              = :ios, '8.0'

end
