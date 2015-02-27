NAME = Flowstone

CC = clang++
CPP_CFLAGS = -Wall -std=gnu++11 -stdlib=libc++ -ferror-limit=1

USER_SOURCES_CPP =\
	Source/Timing.cpp\
	../../Source/Core/Error.cpp\
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
	../../Source/Core/Physics/Engine.cpp\
	../../Source/Core/Physics/CollisionDetector.cpp\
	../../Source/Core/Physics/CollisionResolver.cpp\
	../../Source/User/TorchManager.cpp\
	../../Source/User/Animation/Animator.cpp\
	../../Source/User/Animation/Registry.cpp\
	../../Source/User/Mainflow/PlayState.cpp\
	../../Source/User/AtmosphereColor.cpp\
	../../Source/User/Interpolation/Interpolater.cpp\
	../../Source/User/RendererFeeder.cpp\
	../../Source/User/Rendering/Renderer.cpp\
	../../Source/User/Rendering/WorldRenderer.cpp\
	../../Source/User/Rendering/Backend/OpenGL/Functions.cpp\
	../../Source/User/Rendering/BoneMeshRegistry.cpp\
	../../Source/User/Rendering/Programs.cpp\
	../../Source/User/Rendering/BoneMeshInstances.cpp\
	../../Source/User/Rendering/CommandStream.cpp\
	../../Source/User/Rendering/DrawQueue.cpp\
	../../Source/User/Rendering/Uniforms.cpp\
	../../Source/User/Rendering/Buffers.cpp\
	../../Source/User/Rendering/CullResult.cpp\
	../../Source/User/Rendering/RenderTargets.cpp\
	../../Source/User/Rendering/FullscreenQuad.cpp\
	../../Source/User/Rendering/Textures.cpp\
	../../Source/User/Rendering/StaticMeshes.cpp\
	../../Source/User/Rendering/StaticMeshInstances.cpp\
	../../Source/User/Rendering/MeshHelper.cpp\
	../../Source/User/Rendering/Culler.cpp\
	../../Source/User/Rendering/LightTransforms.cpp\
	../../Source/User/Rendering/DrawSet.cpp\
	../../Source/User/Rendering/BoneDrawSet.cpp\
	../../Source/User/Rendering/StaticDrawSet.cpp\
	../../Source/User/Rendering/PointLightDrawSet.cpp\
	../../Source/User/Rendering/Frustum.cpp\
	../../Source/User/Rendering/Shadow.cpp\
	../../Source/User/Rendering/ShadowBlur.cpp\
	../../Source/User/Rendering/ShadowBasePass.cpp\
	../../Source/User/Rendering/MergePass.cpp\
	../../Source/User/Rendering/GeometryPass.cpp\
	../../Source/User/Rendering/SSAO.cpp\
	../../Source/User/Rendering/SSAOGrainPass.cpp\
	../../Source/User/Rendering/SSAOBlurPass.cpp\
	../../Source/User/Rendering/DownsamplePass.cpp\
	../../Source/User/Rendering/PointLights.cpp\
	../../Source/User/Rendering/PointLightPass.cpp

USER_SOURCES_OBJC = \
	Source/Util.m\
	Source/GameView.m\
	Source/GameAppDelegate.m\
	Source/GameWindow.m\
	Source/GameWindowDelegate.m\
	Source/GameApplication.m

USER_SOURCES_OBJCPP = \
	../../Libraries/Cabi/Library/Source/OSX/Cabi.mm\
	Source/main.mm

USER_HEADER_DIRS =\
	-I../../Libraries/Cabi/Library/Include\
	-I../../Libraries/Conrad/Library/Include\
	-I../../Libraries/Quanta/Library/Include\
	-I../../Source/User\
	-I../../Source\
	-IInclude

USER_FRAMEWORKS = -framework CoreFoundation -framework QuartzCore -framework AppKit -framework OpenGL

BUILD_DIR = ../../Build

USER_OBJECTS =\
	$(patsubst %.cpp,$(BUILD_DIR)/Objects/User/%.o,$(USER_SOURCES_CPP))\
	$(patsubst %.mm,$(BUILD_DIR)/Objects/User/%.o,$(USER_SOURCES_OBJCPP))\
	$(patsubst %.m,$(BUILD_DIR)/Objects/User/%.o,$(USER_SOURCES_OBJC))

USER_OUTPUT_DIR = $(BUILD_DIR)/$(NAME).app/Contents
USER_EXECUTABLE_DIR = $(USER_OUTPUT_DIR)/MacOS
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
	$(CC) $(CFLAGS) $(USER_FRAMEWORKS) $(USER_OBJECTS) -o $(USER_EXECUTABLE_PATH)
	rm -rf $(USER_OUTPUT_DIR)/Resources
	cp -r ../../Resources $(USER_OUTPUT_DIR)/.

all: user

clean:
	rm -rf $(BUILD_DIR)

run: user
	# todo: fix this hack
	rm -rf $(USER_OUTPUT_DIR)/Resources
	cp -r ../../Resources $(USER_OUTPUT_DIR)/.
	$(USER_OUTPUT_DIR)/MacOS/$(NAME)
