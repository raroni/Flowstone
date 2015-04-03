NAME = Flowstone

CC = clang++
CPP_CFLAGS = -Wall -std=gnu++11 -stdlib=libc++ -ferror-limit=1

USER_SOURCES_CPP =\
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
	../../Libraries/Piper/Library/Source/Client.cpp\
	../../Libraries/Piper/Library/Source/AckSet128.cpp\
	../../Libraries/Piper/Library/Source/AckSet32.cpp\
	../../Libraries/Piper/Library/Source/ClientOutBuffer.cpp\
	../../Libraries/Piper/Library/Source/Util.cpp\
	../../Libraries/Piper/Library/Source/ClientIDPool.cpp\
	../../Libraries/Piper/Library/Source/MessageBuffer.cpp\
	../../Libraries/Piper/Library/Source/Server.cpp\
	../../Libraries/Piper/Library/Source/ServerInBuffer.cpp\
	../../Libraries/Piper/Library/Source/ServerOutBuffer.cpp\
	../../Libraries/Piper/Library/Source/Transmission.cpp\
	../../Common/LoopStream.cpp\
	../../Common/GameTime.cpp\
	../../Physics/Engine.cpp\
	../../Physics/CollisionDetector.cpp\
	../../Physics/CollisionResolver.cpp\
	../../Server/Game.cpp\
	../../Server/ClientSet.cpp\
	../../Server/ClientIDPool.cpp\
	../../Server/Net.cpp\
	../../Server/AckHelper.cpp\
	../../Server/PingPong.cpp\
	../../Server/Carrier.cpp\
	../../Client/Game.cpp\
	../../Client/ServerControl.cpp\
	../../Client/ServerControlQueue.cpp\
	../../Client/Screen.cpp\
	../../Client/ScreenSync.cpp\
	../../Client/Net.cpp\
	../../Client/AckHelper.cpp\
	../../Client/TorchManager.cpp\
	../../Client/MainFlow/PlayState.cpp\
	../../Client/AtmosphereColor.cpp\
	../../Client/Interpolation/Interpolater.cpp\
	../../Client/PingPong.cpp\
	../../Client/Carrier.cpp\
	../../Client/Keyboard.cpp\
	../../Client/RendererFeeder.cpp\
	../../Animation/Animator.cpp\
	../../Animation/Registry.cpp\
	../../Rendering/Renderer.cpp\
	../../Rendering/WorldRenderer.cpp\
	../../Rendering/BoneMeshRegistry.cpp\
	../../Rendering/Programs.cpp\
	../../Rendering/BoneMeshInstances.cpp\
	../../Rendering/CommandStream.cpp\
	../../Rendering/DrawQueue.cpp\
	../../Rendering/Uniforms.cpp\
	../../Rendering/Buffers.cpp\
	../../Rendering/CullResult.cpp\
	../../Rendering/RenderTargets.cpp\
	../../Rendering/FullscreenQuad.cpp\
	../../Rendering/Textures.cpp\
	../../Rendering/StaticMeshes.cpp\
	../../Rendering/StaticMeshInstances.cpp\
	../../Rendering/MeshHelper.cpp\
	../../Rendering/Culler.cpp\
	../../Rendering/LightTransforms.cpp\
	../../Rendering/DrawSet.cpp\
	../../Rendering/BoneDrawSet.cpp\
	../../Rendering/StaticDrawSet.cpp\
	../../Rendering/PointLightDrawSet.cpp\
	../../Rendering/Frustum.cpp\
	../../Rendering/Shadow.cpp\
	../../Rendering/ShadowBlur.cpp\
	../../Rendering/ShadowBasePass.cpp\
	../../Rendering/MergePass.cpp\
	../../Rendering/GeometryPass.cpp\
	../../Rendering/SSAO.cpp\
	../../Rendering/SSAOGrainPass.cpp\
	../../Rendering/SSAOBlurPass.cpp\
	../../Rendering/DownsamplePass.cpp\
	../../Rendering/PointLights.cpp\
	../../Rendering/PointLightPass.cpp\
	../../Sys/GFX/OpenGL/Source/SysGFX.cpp\
	../../Sys/Net/Source/SysNet.cpp\
	Source/SysNet.cpp\
	Source/SysThread.cpp\
	Source/SysTime.cpp\
	Source/main.cpp

USER_SOURCES_OBJC = \
	Source/GameWindow.m\
	Source/GameApplication.m

USER_SOURCES_OBJCPP = \
	Source/SysFile.mm\
	Source/GameAppDelegate.mm\
	Source/GameWindowDelegate.mm\
	Source/SysKey.mm\
	Source/ClientPlatform.mm

USER_HEADER_DIRS =\
	-I../../Libraries/Conrad/Library/Include\
	-I../../Libraries/Quanta/Library/Include\
	-I../../Libraries/Piper/Library/Include\
	-I../../Sys/File/Include\
	-I../../Sys/Net/Include\
	-I../../Sys/Key/Include\
	-I../../Sys/GFX/Include\
	-I../../Sys/GFX/OpenGL/Include\
	-I../../Sys/Time/Include\
	-I../../Sys/Thread/Include\
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


TEST_SOURCES =\
	../../Libraries/Quanta/Library/Source/Math/Matrix4.cpp\
	../../Libraries/Quanta/Library/Source/Math/Quaternion.cpp\
	../../Libraries/Quanta/Library/Source/Math/Vector3.cpp\
	../../Libraries/Quanta/Library/Source/Math/Vector4.cpp\
	../../Libraries/Quanta/Library/Source/Geometry/Transform.cpp\
	../../Libraries/Quanta/Library/Source/Geometry/TransformFactory3D.cpp\
	../../Libraries/Quanta/Library/Source/Util.cpp\
	../../Libraries/Piper/Library/Source/Util.cpp\
	../../Libraries/Piper/Library/Source/AckSet128.cpp\
	../../Libraries/Piper/Library/Source/AckSet32.cpp\
	../../Physics/Engine.cpp\
	../../Physics/CollisionResolver.cpp\
	../../Physics/CollisionDetector.cpp\
	../../Common/LoopStream.cpp\
	../../Test/main.cpp

TEST_HEADER_DIRS =\
	-I../../Libraries/Conrad/Library/Include\
	-I../../Libraries/Quanta/Library/Include\
	-I../../Libraries/Piper/Library/Include\
	-I../../Source\
	-I../../Source/User\
	-I../..

TEST_OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/Objects/Test/%.o,$(TEST_SOURCES))

TEST_EXECUTABLE_PATH = $(BUILD_DIR)/Test/Test

test: $(TEST_EXECUTABLE_PATH)
	$(TEST_EXECUTABLE_PATH)

$(TEST_EXECUTABLE_PATH): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(TEST_HEADER_DIRS) $(TEST_OBJECTS) -o $@

$(BUILD_DIR)/Objects/Test/%.o : %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPP_CFLAGS) $(TEST_HEADER_DIRS) $< -c -o $@
