workspace "Nanamichiaki"		-- �������
	architecture "x64"			-- �ܹ�

	configurations
	{
		"Debug",				-- ��ȫ����
		"Release",				-- ���ֵ���
		"Dist"					-- �����汾
	}

-- ���ɵ��ļ����Ŀ¼��ϵͳ��_ģʽ��_�ܹ���
outputdir = "%{cfg.system}_%{cfg.buildcfg}_%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Nanamichiaki/vendor/GLFW/include"

include "Nanamichiaki/vendor/GLFW"

-- NNMCAK Engine �������
project "Nanamichiaki"
	location "Nanamichiaki"		-- λ�ã��������Ŀ��Ŀ¼
	kind "SharedLib"			-- ������Ŀ���ͣ������
	language "C++"				-- ��������
	
								-- ���ñ���Ķ�����Ŀ���Ŀ��Ŀ¼
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
								-- ���ù�����ĿʱӦ���ö���������м��ļ���Ŀ¼
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
								-- ���Ԥ����ͷ
	pchheader "NNMCAKpch.h"
								-- Windows����
	pchsource "Nanamichiaki/src/NNMCAKpch.cpp"
								-- ���ļ���������Ŀ��
	files
	{
		"%{prj.name}/src/**.h", -- ** ���еݹ�ƥ���ļ�
		"%{prj.name}/src/**.cpp"
	}

	includedirs					-- ָ���������İ����ļ�����·��
	{
		"%{prj.name}/src",
								-- spdlog ��������־��
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"		-- ������ ������������������Ϊ�ض�����
		cppdialect "C++17"
		staticruntime "On"		-- ��̬����ʱ ��<RuntimeLibrary>����Ϊ�����̡߳�
								-- ָ��Ŀ�����ϵͳ����С�����汾 WIN SDK
		systemversion "latest"

								-- ��Ԥ�������������������ӵ���Ŀ�� �궨��
		defines
		{
			"NNMCAK_PLATFORM_WINDOWS",
			"NNMCAK_BUILD_DLL"
		}

								-- ָ��������ɺ�Ҫ���е� shell ����
		postbuildcommands
		{
								-- ����dll�ļ�,�������⣺��Ҫ�ȴ����ļ��У�������Ϊ�ļ�
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "NNMCAK_DEBUG"
		symbols "On"			-- ���Է��Ŵ�
	
	filter "configurations:Release"
		defines "NNMCAK_RELEASE"
		optimize "On"			-- �Ż�����

	filter "configurations:Dist"
		defines "NNMCAK_DIST"
		optimize "On"


-- Sandbox �������
project "Sandbox"
	location "Sandbox"			-- λ�ã��������Ŀ��Ŀ¼
	kind "ConsoleApp"			-- ������Ŀ���ͣ�����̨��������Ӧ�ó���
	language "C++"				-- ��������
	
								-- ���ñ���Ķ�����Ŀ���Ŀ��Ŀ¼
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
								-- ���ù�����ĿʱӦ���ö���������м��ļ���Ŀ¼
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
								-- ���ļ���������Ŀ��
	files
	{
		"%{prj.name}/src/**.h", -- ** ���еݹ�ƥ���ļ�
		"%{prj.name}/src/**.cpp"
	}

	includedirs					-- ָ���������İ����ļ�����·��
	{
								-- spdlog ��������־��
		"Nanamichiaki/vendor/spdlog/include",
		"Nanamichiaki/src"
	}
								-- ָ��Ҫ���ӵĿ����Ŀ���б�
	links
	{
		"Nanamichiaki"
	}

	filter "system:windows"		-- ������ ������������������Ϊ�ض�����
		cppdialect "C++17"
		staticruntime "On"		-- ��̬����ʱ ��<RuntimeLibrary>����Ϊ�����̡߳�
								-- ָ��Ŀ�����ϵͳ����С�����汾 WIN SDK
		systemversion "latest"

								-- ��Ԥ�������������������ӵ���Ŀ�� �궨��
		defines
		{
			"NNMCAK_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "NNMCAK_DEBUG"
		symbols "On"			-- ���Է��Ŵ�
	
	filter "configurations:Release"
		defines "NNMCAK_RELEASE"
		optimize "On"			-- �Ż�����

	filter "configurations:Dist"
		defines "NNMCAK_DIST"
		optimize "On"