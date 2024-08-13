workspace "Nanamichiaki"		-- 解决方案
	architecture "x64"			-- 架构

	configurations
	{
		"Debug",				-- 完全调试
		"Release",				-- 部分调试
		"Dist"					-- 发布版本
	}

-- 生成的文件输出目录：系统名_模式名_架构名
outputdir = "%{cfg.system}_%{cfg.buildcfg}_%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Nanamichiaki/vendor/GLFW/include"

include "Nanamichiaki/vendor/GLFW"

-- NNMCAK Engine 相关配置
project "Nanamichiaki"
	location "Nanamichiaki"		-- 位置，相对于项目根目录
	kind "SharedLib"			-- 生成项目类型：共享库
	language "C++"				-- 语言类型
	
								-- 设置编译的二进制目标的目标目录
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
								-- 设置构建项目时应放置对象和其他中间文件的目录
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
								-- 添加预编译头
	pchheader "NNMCAKpch.h"
								-- Windows特有
	pchsource "Nanamichiaki/src/NNMCAKpch.cpp"
								-- 将文件包括在项目中
	files
	{
		"%{prj.name}/src/**.h", -- ** 进行递归匹配文件
		"%{prj.name}/src/**.cpp"
	}

	includedirs					-- 指定编译器的包含文件搜索路径
	{
		"%{prj.name}/src",
								-- spdlog 第三方日志库
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"		-- 过滤器 将后续构建设置限制为特定环境
		cppdialect "C++17"
		staticruntime "On"		-- 静态运行时 将<RuntimeLibrary>设置为“多线程”
								-- 指定目标操作系统的最小和最大版本 WIN SDK
		systemversion "latest"

								-- 将预处理器或编译器符号添加到项目中 宏定义
		defines
		{
			"NNMCAK_PLATFORM_WINDOWS",
			"NNMCAK_BUILD_DLL"
		}

								-- 指定构建完成后要运行的 shell 命令
		postbuildcommands
		{
								-- 复制dll文件,发现问题：需要先创建文件夹，否则复制为文件
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "NNMCAK_DEBUG"
		symbols "On"			-- 调试符号打开
	
	filter "configurations:Release"
		defines "NNMCAK_RELEASE"
		optimize "On"			-- 优化符号

	filter "configurations:Dist"
		defines "NNMCAK_DIST"
		optimize "On"


-- Sandbox 相关配置
project "Sandbox"
	location "Sandbox"			-- 位置，相对于项目根目录
	kind "ConsoleApp"			-- 生成项目类型：控制台、命令行应用程序
	language "C++"				-- 语言类型
	
								-- 设置编译的二进制目标的目标目录
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
								-- 设置构建项目时应放置对象和其他中间文件的目录
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
								-- 将文件包括在项目中
	files
	{
		"%{prj.name}/src/**.h", -- ** 进行递归匹配文件
		"%{prj.name}/src/**.cpp"
	}

	includedirs					-- 指定编译器的包含文件搜索路径
	{
								-- spdlog 第三方日志库
		"Nanamichiaki/vendor/spdlog/include",
		"Nanamichiaki/src"
	}
								-- 指定要链接的库和项目的列表
	links
	{
		"Nanamichiaki"
	}

	filter "system:windows"		-- 过滤器 将后续构建设置限制为特定环境
		cppdialect "C++17"
		staticruntime "On"		-- 静态运行时 将<RuntimeLibrary>设置为“多线程”
								-- 指定目标操作系统的最小和最大版本 WIN SDK
		systemversion "latest"

								-- 将预处理器或编译器符号添加到项目中 宏定义
		defines
		{
			"NNMCAK_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "NNMCAK_DEBUG"
		symbols "On"			-- 调试符号打开
	
	filter "configurations:Release"
		defines "NNMCAK_RELEASE"
		optimize "On"			-- 优化符号

	filter "configurations:Dist"
		defines "NNMCAK_DIST"
		optimize "On"