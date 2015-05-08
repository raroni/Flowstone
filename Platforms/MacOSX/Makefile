NAME = Flowstone

CC = clang++
CPP_CFLAGS = -Wall -std=gnu++11 -stdlib=libc++ -ferror-limit=1

USER_SOURCES_CPP =\
	../../Misc/Error.cpp\
	../../Misc/LoopStream.cpp\
	../../Misc/IntegerPool.cpp\
	../../Misc/HandleList.cpp\
	../../Misc/GameTime.cpp\
	../../Libraries/Quanta/Source/Math/Vector2.cpp\
	../../Libraries/Quanta/Source/Math/Vector3.cpp\
	../../Libraries/Quanta/Source/Math/Vector4.cpp\
	../../Libraries/Quanta/Source/Math/Matrix4.cpp\
	../../Libraries/Quanta/Source/Math/Quaternion.cpp\
	../../Libraries/Quanta/Source/Geometry/Transform.cpp\
	../../Libraries/Quanta/Source/Geometry/TransformFactory3D.cpp\
	../../Libraries/Quanta/Source/Geometry/Plane.cpp\
	../../Libraries/Quanta/Source/Geometry/Transformer.cpp\
	../../Libraries/Quanta/Source/Random.cpp\
	../../Libraries/Quanta/Source/Util.cpp\
	../../Libraries/Fixie/Library/Source/Trig.cpp\
	../../Libraries/Fixie/Library/Source/Geometry.cpp\
	../../Libraries/Fixie/Library/Source/Util.cpp\
	../../Libraries/Fixie/Library/Source/Vector2.cpp\
	../../Libraries/Fixie/Library/Source/Vector3.cpp\
	../../Libraries/Fixie/Library/Source/Matrix4.cpp\
	../../Libraries/Fixie/Library/Source/Quaternion.cpp\
	../../Libraries/Fixie/Library/Source/TransformFactory.cpp\
	../../Libraries/Piper/Source/Client.cpp\
	../../Libraries/Piper/Source/AckSet128.cpp\
	../../Libraries/Piper/Source/AckSet32.cpp\
	../../Libraries/Piper/Source/ClientOutBuffer.cpp\
	../../Libraries/Piper/Source/Util.cpp\
	../../Libraries/Piper/Source/ClientIDPool.cpp\
	../../Libraries/Piper/Source/MessageBuffer.cpp\
	../../Libraries/Piper/Source/Server.cpp\
	../../Libraries/Piper/Source/ServerInBuffer.cpp\
	../../Libraries/Piper/Source/ServerOutBuffer.cpp\
	../../Libraries/Piper/Source/Transmission.cpp\
	../../Physics/Engine.cpp\
	../../Physics/CollisionDetector.cpp\
	../../Physics/Integrator.cpp\
	../../Physics/BodyList.cpp\
	../../Physics/SphereColliderList.cpp\
	../../Physics/KinematicDriverList.cpp\
	../../Physics/DynamicDriverList.cpp\
	../../Physics/CollisionResolver.cpp\
	../../Database/ComponentManager.cpp\
	../../Database/EntityManager.cpp\
	../../Server/Game.cpp\
	../../Server/ClientSet.cpp\
	../../Server/ClientIDPool.cpp\
	../../Server/Net.cpp\
	../../Server/AckHelper.cpp\
	../../Server/PingPong.cpp\
	../../Server/Carrier.cpp\
	../../Client/Game.cpp\
	../../Client/Database.cpp\
	../../Client/CameraControl.cpp\
	../../Client/CommandList.cpp\
	../../Client/LocalSimulationDriver.cpp\
	../../Client/MathConversion.cpp\
	../../Client/ServerControl.cpp\
	../../Client/ServerControlQueue.cpp\
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
	../../Simulation/Control.cpp\
	../../Simulation/Steering/SteeringSystem.cpp\
	../../Simulation/Trees.cpp\
	../../Simulation/Pathfinding/PathfindingSystem.cpp\
	../../Simulation/Pathfinding/Map.cpp\
	../../Simulation/Pathfinding/MapDirectionList.cpp\
	../../Simulation/Pathfinding/MapNeighbourIterator.cpp\
	../../Simulation/Pathfinding/AStarPriorityQueue.cpp\
	../../Simulation/Pathfinding/AStarCostMap.cpp\
	../../Simulation/Pathfinding/AStarCostBucket.cpp\
	../../Simulation/Pathfinding/AStar.cpp\
	../../Simulation/Steering/SteeringList.cpp\
	../../Simulation/Drag/DragSystem.cpp\
	../../Simulation/Mode.cpp\
	../../Simulation/PhysicsHack.cpp\
	../../Simulation/PlayMode.cpp\
	../../Simulation/ResourceSystem.cpp\
	../../Simulation/CommandList.cpp\
	../../Simulation/EventList.cpp\
	../../Simulation/Database.cpp\
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
	-I../../Libraries/Conrad/Include\
	-I../../Libraries/Quanta/Include\
	-I../../Libraries/Fixie/Library/Include\
	-I../../Libraries/Piper/Include\
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
	../../Libraries/Quanta/Source/Math/Matrix4.cpp\
	../../Libraries/Quanta/Source/Math/Quaternion.cpp\
	../../Libraries/Quanta/Source/Math/Vector3.cpp\
	../../Libraries/Quanta/Source/Math/Vector4.cpp\
	../../Libraries/Quanta/Source/Geometry/Transform.cpp\
	../../Libraries/Quanta/Source/Geometry/TransformFactory3D.cpp\
	../../Libraries/Quanta/Source/Util.cpp\
	../../Libraries/Piper/Source/Util.cpp\
	../../Libraries/Piper/Source/AckSet128.cpp\
	../../Libraries/Piper/Source/AckSet32.cpp\
	../../Libraries/Fixie/Library/Source/Trig.cpp\
	../../Libraries/Fixie/Library/Source/Util.cpp\
	../../Libraries/Fixie/Library/Source/Vector2.cpp\
	../../Libraries/Fixie/Library/Source/Vector3.cpp\
	../../Libraries/Fixie/Library/Source/Matrix4.cpp\
	../../Libraries/Fixie/Library/Source/Quaternion.cpp\
	../../Misc/Error.cpp\
	../../Misc/IntegerPool.cpp\
	../../Misc/HandleList.cpp\
	../../Physics/Engine.cpp\
	../../Physics/CollisionResolver.cpp\
	../../Physics/Integrator.cpp\
	../../Physics/CollisionDetector.cpp\
	../../Physics/SphereColliderList.cpp\
	../../Physics/BodyList.cpp\
	../../Physics/DynamicDriverList.cpp\
	../../Physics/KinematicDriverList.cpp\
	../../Simulation/Pathfinding/AStarPriorityQueue.cpp\
	../../Simulation/Pathfinding/AStarCostMap.cpp\
	../../Simulation/Pathfinding/AStarCostBucket.cpp\
	../../Simulation/Pathfinding/Map.cpp\
	../../Simulation/Pathfinding/AStar.cpp\
	../../Simulation/Pathfinding/MapDirectionList.cpp\
	../../Simulation/Pathfinding/MapNeighbourIterator.cpp\
	../../Misc/LoopStream.cpp\
	../../Test/main.cpp

TEST_HEADER_DIRS =\
	-I../../Libraries/Conrad/Include\
	-I../../Libraries/Quanta/Include\
	-I../../Libraries/Piper/Include\
	-I../../Libraries/Fixie/Library/Include\
	-I../../Sys/Time/Include\
	-I../../Test\
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
