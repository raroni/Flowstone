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
	../../Common/Piper/Transmission.cpp\
	../../GameClient/GameClient.cpp\
	../../GameClient/GameClientInput.cpp\
	../../GameClient/KeyboardInput.cpp\
	../../GameClient/TorchManager.cpp\
	../../GameClient/Animation/Animator.cpp\
	../../GameClient/Animation/Registry.cpp\
	../../GameClient/Mainflow/PlayState.cpp\
	../../GameClient/AtmosphereColor.cpp\
	../../GameClient/Interpolation/Interpolater.cpp\
	../../GameClient/Keyboard.cpp\
	../../GameClient/RendererFeeder.cpp\
	../../GameClient/Rendering/Renderer.cpp\
	../../GameClient/Rendering/WorldRenderer.cpp\
	../../GameClient/Rendering/BoneMeshRegistry.cpp\
	../../GameClient/Rendering/Programs.cpp\
	../../GameClient/Rendering/BoneMeshInstances.cpp\
	../../GameClient/Rendering/CommandStream.cpp\
	../../GameClient/Rendering/DrawQueue.cpp\
	../../GameClient/Rendering/Uniforms.cpp\
	../../GameClient/Rendering/Buffers.cpp\
	../../GameClient/Rendering/CullResult.cpp\
	../../GameClient/Rendering/RenderTargets.cpp\
	../../GameClient/Rendering/FullscreenQuad.cpp\
	../../GameClient/Rendering/Textures.cpp\
	../../GameClient/Rendering/StaticMeshes.cpp\
	../../GameClient/Rendering/StaticMeshInstances.cpp\
	../../GameClient/Rendering/MeshHelper.cpp\
	../../GameClient/Rendering/Culler.cpp\
	../../GameClient/Rendering/LightTransforms.cpp\
	../../GameClient/Rendering/DrawSet.cpp\
	../../GameClient/Rendering/BoneDrawSet.cpp\
	../../GameClient/Rendering/StaticDrawSet.cpp\
	../../GameClient/Rendering/PointLightDrawSet.cpp\
	../../GameClient/Rendering/Frustum.cpp\
	../../GameClient/Rendering/Shadow.cpp\
	../../GameClient/Rendering/ShadowBlur.cpp\
	../../GameClient/Rendering/ShadowBasePass.cpp\
	../../GameClient/Rendering/MergePass.cpp\
	../../GameClient/Rendering/GeometryPass.cpp\
	../../GameClient/Rendering/SSAO.cpp\
	../../GameClient/Rendering/SSAOGrainPass.cpp\
	../../GameClient/Rendering/SSAOBlurPass.cpp\
	../../GameClient/Rendering/DownsamplePass.cpp\
	../../GameClient/Rendering/PointLights.cpp\
	../../GameClient/Rendering/PointLightPass.cpp\
	../../Sys/GFX/OpenGL/Source/SysGFX.cpp

USER_SOURCES_OBJC = \
	Source/Util.m\
	Source/GameAppDelegate.m\
	Source/GameWindow.m\
	Source/GameWindowDelegate.m\
	Source/GameApplication.m

USER_SOURCES_OBJCPP = \
	Source/main.mm\
	Source/SysFile.mm

USER_HEADER_DIRS =\
	-I../../Libraries/Conrad/Library/Include\
	-I../../Libraries/Quanta/Library/Include\
	-I../../Sys/File/Include\
	-I../../Sys/Net/Include\
	-I../../Sys/GFX/Include\
	-I../../Sys/GFX/OpenGL/Include\
	-I../../GameClient\
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
