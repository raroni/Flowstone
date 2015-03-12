NAME = Flowstone

CC = clang++
CPP_CFLAGS = -Wall -std=gnu++11 -stdlib=libc++ -ferror-limit=1

USER_SOURCES_CPP =\
	Source/Timing.cpp\
	../../Common/Error.cpp\
	../../Libraries/Quanta/Library/Source/Math/Vector2.cpp\
	../../Libraries/Quanta/Library/Source/Math/Vector3.cpp\
	../../Libraries/Quanta/Library/Source/Math/Vector4.cpp\
	../../Libraries/Quanta/Library/Source/Math/Matrix4.cpp\
	../../Libraries/Quanta/Library/Source/Math/Quaternion.cpp\
	../../Libraries/Quanta/Library/Source/Geometry/Transform.cpp\
	../../Libraries/Quanta/Library/Source/Geometry/TransformFactory3D.cpp\
	../../Libraries/Quanta/Library/Source/Geometry/Plane.cpp\
	../../Libraries/Quanta/Library/Source/Geometry/Transformer.cpp\
	../../Libraries/Quanta/Library/Source/Random.cpp\
	../../Libraries/Quanta/Library/Source/Util.cpp\
	../../Common/Physics/Engine.cpp\
	../../Common/Physics/CollisionDetector.cpp\
	../../Common/Physics/CollisionResolver.cpp\
	../../Common/Piper/Client.cpp\
	../../Common/Piper/ClientOutBuffer.cpp\
	../../Common/Piper/ClientIDPool.cpp\
	../../Common/Piper/MessageBuffer.cpp\
	../../Common/Piper/Server.cpp\
	../../Common/Piper/ServerInBuffer.cpp\
	../../Common/Piper/ServerOutBuffer.cpp\
	../../Common/Piper/Transmission.cpp\
	../../ServerGame/ServerGame.cpp\
	../../ServerGame/ServerPingPong.cpp\
	../../UserGame/UserGame.cpp\
	../../UserGame/ClientGame.cpp\
	../../UserGame/TorchManager.cpp\
	../../UserGame/Animation/Animator.cpp\
	../../UserGame/Animation/Registry.cpp\
	../../UserGame/Mainflow/PlayState.cpp\
	../../UserGame/AtmosphereColor.cpp\
	../../UserGame/Interpolation/Interpolater.cpp\
	../../UserGame/PingPong.cpp\
	../../UserGame/Keyboard.cpp\
	../../UserGame/RendererFeeder.cpp\
	../../UserGame/Rendering/Renderer.cpp\
	../../UserGame/Rendering/WorldRenderer.cpp\
	../../UserGame/Rendering/BoneMeshRegistry.cpp\
	../../UserGame/Rendering/Programs.cpp\
	../../UserGame/Rendering/BoneMeshInstances.cpp\
	../../UserGame/Rendering/CommandStream.cpp\
	../../UserGame/Rendering/DrawQueue.cpp\
	../../UserGame/Rendering/Uniforms.cpp\
	../../UserGame/Rendering/Buffers.cpp\
	../../UserGame/Rendering/CullResult.cpp\
	../../UserGame/Rendering/RenderTargets.cpp\
	../../UserGame/Rendering/FullscreenQuad.cpp\
	../../UserGame/Rendering/Textures.cpp\
	../../UserGame/Rendering/StaticMeshes.cpp\
	../../UserGame/Rendering/StaticMeshInstances.cpp\
	../../UserGame/Rendering/MeshHelper.cpp\
	../../UserGame/Rendering/Culler.cpp\
	../../UserGame/Rendering/LightTransforms.cpp\
	../../UserGame/Rendering/DrawSet.cpp\
	../../UserGame/Rendering/BoneDrawSet.cpp\
	../../UserGame/Rendering/StaticDrawSet.cpp\
	../../UserGame/Rendering/PointLightDrawSet.cpp\
	../../UserGame/Rendering/Frustum.cpp\
	../../UserGame/Rendering/Shadow.cpp\
	../../UserGame/Rendering/ShadowBlur.cpp\
	../../UserGame/Rendering/ShadowBasePass.cpp\
	../../UserGame/Rendering/MergePass.cpp\
	../../UserGame/Rendering/GeometryPass.cpp\
	../../UserGame/Rendering/SSAO.cpp\
	../../UserGame/Rendering/SSAOGrainPass.cpp\
	../../UserGame/Rendering/SSAOBlurPass.cpp\
	../../UserGame/Rendering/DownsamplePass.cpp\
	../../UserGame/Rendering/PointLights.cpp\
	../../UserGame/Rendering/PointLightPass.cpp\
	../../Sys/GFX/OpenGL/Source/SysGFX.cpp\
	../../Sys/Net/Source/SysNet.cpp\
	Source/SysNet.cpp

USER_SOURCES_OBJC = \
	Source/Util.m\
	Source/GameAppDelegate.m\
	Source/GameWindow.m\
	Source/GameWindowDelegate.m\
	Source/GameApplication.m

USER_SOURCES_OBJCPP = \
	Source/main.mm\
	Source/SysFile.mm\
	Source/SysKey.mm

USER_HEADER_DIRS =\
	-I../../Libraries/Conrad/Library/Include\
	-I../../Libraries/Quanta/Library/Include\
	-I../../Sys/File/Include\
	-I../../Sys/Net/Include\
	-I../../Sys/Key/Include\
	-I../../Sys/GFX/Include\
	-I../../Sys/GFX/OpenGL/Include\
	-I../../UserGame\
	-I../..\
	-IInclude

USER_FRAMEWORKS = -framework CoreFoundation -framework QuartzCore -framework AppKit -framework OpenGL

BUILD_DIR = ../../Build

USER_OBJECTS =\
	$(patsubst %.cpp,$(BUILD_DIR)/Objects/User/%.o,$(USER_SOURCES_CPP))\
	$(patsubst %.mm,$(BUILD_DIR)/Objects/User/%.o,$(USER_SOURCES_OBJCPP))\
	$(patsubst %.m,$(BUILD_DIR)/Objects/User/%.o,$(USER_SOURCES_OBJC))

USER_OUTPUT_DIR = $(BUILD_DIR)/$(NAME).app/Contents
USER_EXECUTABLE_DIR = $(USER_OUTPUT_DIR)/MacOS
USER_RESOURCE_DIR = $(USER_OUTPUT_DIR)/Resources
USER_EXECUTABLE_PATH = $(USER_EXECUTABLE_DIR)/$(NAME)

$(BUILD_DIR)/Objects/User/%.o : %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPP_CFLAGS) $(USER_HEADER_DIRS) $< -c -o $@

$(BUILD_DIR)/Objects/User/%.o : %.mm
	mkdir -p $(dir $@)
	$(CC) $(CPP_CFLAGS) $(USER_HEADER_DIRS) $< -c -o $@

$(BUILD_DIR)/Objects/User/%.o : %.m
	mkdir -p $(dir $@)
	$(CC) $(USER_HEADER_DIRS) $< -c -o $@

user: $(USER_EXECUTABLE_PATH)

$(USER_EXECUTABLE_PATH): $(USER_OBJECTS)
	mkdir -p $(USER_EXECUTABLE_DIR)
	mkdir -p $(USER_RESOURCE_DIR)
	$(CC) $(CFLAGS) $(USER_FRAMEWORKS) $(USER_OBJECTS) -o $(USER_EXECUTABLE_PATH)
	rm -rf $(USER_OUTPUT_DIR)/Shaders
	cp -r ../../Shaders/GLSL $(USER_RESOURCE_DIR)/Shaders

all: user

clean:
	rm -rf $(BUILD_DIR)

run: user
	$(USER_OUTPUT_DIR)/MacOS/$(NAME)
