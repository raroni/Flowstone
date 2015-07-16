CLIENT_OBJ_CPP_SOURCES =\
  $(PLATFORM_DIR)/Source/SysFile.mm\
  $(PLATFORM_DIR)/Source/GameAppDelegate.mm\
  $(PLATFORM_DIR)/Source/GameWindowDelegate.mm\
  $(PLATFORM_DIR)/Source/SysKey.mm\
  $(PLATFORM_DIR)/Source/ClientPlatform.mm

CLIENT_OBJ_C_SOURCES =\
  $(PLATFORM_DIR)/Source/GameWindow.m\
  $(PLATFORM_DIR)/Source/GameApplication.m

CLIENT_CPP_SOURCES =\
  Misc/Error.cpp\
  Misc/LoopStream.cpp\
  Misc/FrameAllocator.cpp\
  Misc/IntegerPool.cpp\
  Misc/HandleList.cpp\
  Misc/GameTime.cpp\
  Libraries/Quanta/Source/Math/Vector2.cpp\
  Libraries/Quanta/Source/Math/Vector3.cpp\
  Libraries/Quanta/Source/Math/Vector4.cpp\
  Libraries/Quanta/Source/Math/Matrix4.cpp\
  Libraries/Quanta/Source/Math/Quaternion.cpp\
  Libraries/Quanta/Source/Geometry/Transform.cpp\
  Libraries/Quanta/Source/Geometry/TransformFactory3D.cpp\
  Libraries/Quanta/Source/Geometry/Plane.cpp\
  Libraries/Quanta/Source/Geometry/Transformer.cpp\
  Libraries/Quanta/Source/Random.cpp\
  Libraries/Quanta/Source/Util.cpp\
  Libraries/Fixie/Library/Source/Trig.cpp\
  Libraries/Fixie/Library/Source/Geometry.cpp\
  Libraries/Fixie/Library/Source/Util.cpp\
  Libraries/Fixie/Library/Source/Vector2.cpp\
  Libraries/Fixie/Library/Source/Vector3.cpp\
  Libraries/Fixie/Library/Source/Matrix4.cpp\
  Libraries/Fixie/Library/Source/Quaternion.cpp\
  Libraries/Fixie/Library/Source/TransformFactory.cpp\
  Libraries/Piper/Source/Client.cpp\
  Libraries/Piper/Source/AckSet128.cpp\
  Libraries/Piper/Source/AckSet32.cpp\
  Libraries/Piper/Source/ClientOutBuffer.cpp\
  Libraries/Piper/Source/Util.cpp\
  Libraries/Piper/Source/ClientIDPool.cpp\
  Libraries/Piper/Source/MessageBuffer.cpp\
  Libraries/Piper/Source/Server.cpp\
  Libraries/Piper/Source/ServerInBuffer.cpp\
  Libraries/Piper/Source/ServerOutBuffer.cpp\
  Libraries/Piper/Source/Transmission.cpp\
  Libraries/Watson/Source/System.cpp\
  Libraries/Watson/Source/Board.cpp\
  Libraries/Watson/Source/NodeTypes.cpp\
  Libraries/Watson/Source/ResponseBuffer.cpp\
  Libraries/Watson/Source/BoardCollection.cpp\
  Libraries/Watson/Source/Stream.cpp\
  Libraries/Watson/Source/ActionStreamCollection.cpp\
  Libraries/Watson/Source/Node.cpp\
  Libraries/Watson/Source/Update.cpp\
  Libraries/Watson/Source/Server.cpp\
  Libraries/Watson/Source/PriorityNode.cpp\
  Libraries/Watson/Source/SequenceNode.cpp\
  Libraries/Watson/Source/LoopNode.cpp\
  Libraries/Watson/Source/InverterNode.cpp\
  Libraries/Watson/Source/ConcurrentNode.cpp\
  Libraries/Watson/Source/FailDummyNode.cpp\
  Libraries/Watson/Source/RunDummyNode.cpp\
  Libraries/Watson/Source/TraversalFlow.cpp\
  Libraries/Watson/Source/NodeStack.cpp\
  Libraries/Watson/Source/ResetFlow.cpp\
  Libraries/Watson/Source/StateCollection.cpp\
  Libraries/Watson/Source/TypeDefinition.cpp\
  Libraries/Watson/Source/TypeList.cpp\
  Libraries/Watson/Source/InstanceOrderingCollection.cpp\
  Libraries/Watson/Source/InstanceList.cpp\
  Physics/Engine.cpp\
  Physics/CollisionDetector.cpp\
  Physics/Integrator.cpp\
  Physics/BodyList.cpp\
  Physics/SphereColliderList.cpp\
  Physics/KinematicDriverList.cpp\
  Physics/DynamicDriverList.cpp\
  Physics/CollisionResolver.cpp\
  Actions/System.cpp\
  Actions/NewRequests.cpp\
  Actions/PendingRequests.cpp\
  Actions/Executions.cpp\
  Actions/ExecutionList.cpp\
  Actions/RequestMap.cpp\
  Actions/InstanceHandleSet.cpp\
  Actions/Instance.cpp\
  Actions/InstanceList.cpp\
  Actions/Request.cpp\
  Actions/ActionOptionsSet.cpp\
  Actions/ActionSetup.cpp\
  Actions/Action.cpp\
  Actions/WoodAcquisitionAction.cpp\
  Actions/ReachTargetAction.cpp\
  Behavior/System.cpp\
  Behavior/Server.cpp\
  Behavior/NodeTypes.cpp\
  Behavior/TreeTypes.cpp\
  Behavior/TypeDefinitionHelper.cpp\
  Behavior/ThreatCheckNode.cpp\
  Behavior/WoodCheckNode.cpp\
  Behavior/WoodAcquisitionNode.cpp\
  Behavior/WorkerTreeType.cpp\
  Database/ComponentManager.cpp\
  Database/EntityManager.cpp\
  Server/Game.cpp\
  Server/ClientSet.cpp\
  Server/ClientIDPool.cpp\
  Server/Net.cpp\
  Server/AckHelper.cpp\
  Server/PingPong.cpp\
  Server/Carrier.cpp\
  Client/Game.cpp\
  Client/Direction/Direction.cpp\
  Client/Direction/DirectionInstanceList.cpp\
  Client/Direction/DirectionSteering.cpp\
  Client/Direction/DirectionEventList.cpp\
  Client/Database.cpp\
  Client/CameraControl.cpp\
  Client/CommandList.cpp\
  Client/LocalSimulationDriver.cpp\
  Client/MathConversion.cpp\
  Client/ServerControl.cpp\
  Client/ServerControlQueue.cpp\
  Client/Net.cpp\
  Client/AckHelper.cpp\
  Client/TorchManager.cpp\
  Client/MainFlow/PlayState.cpp\
  Client/AtmosphereColor.cpp\
  Client/Interpolation.cpp\
  Client/PingPong.cpp\
  Client/Carrier.cpp\
  Client/Keyboard.cpp\
  Client/RenderFeed.cpp\
  Simulation/Control.cpp\
  Simulation/Steering/SteeringSystem.cpp\
  Simulation/Steering/SteeringList.cpp\
  Simulation/Targeting/TargetingList.cpp\
  Simulation/Targeting/TargetingSystem.cpp\
  Simulation/Trees.cpp\
  Simulation/Pathfinding/PathfindingSystem.cpp\
  Simulation/Pathfinding/Map.cpp\
  Simulation/Pathfinding/MapDirectionList.cpp\
  Simulation/Pathfinding/MapNeighbourIterator.cpp\
  Simulation/Pathfinding/AStarPriorityQueue.cpp\
  Simulation/Pathfinding/AStarCostMap.cpp\
  Simulation/Pathfinding/AStarCostBucket.cpp\
  Simulation/Pathfinding/AStar.cpp\
  Simulation/Ticket/TicketSystem.cpp\
  Simulation/Ticket/TicketRequestList.cpp\
  Simulation/Ticket/TicketTargetList.cpp\
  Simulation/Drag/DragSystem.cpp\
  Simulation/Mode.cpp\
  Simulation/PhysicsHack.cpp\
  Simulation/PlayMode.cpp\
  Simulation/Harvest/HarvestSystem.cpp\
  Simulation/Harvest/HarvestResourceList.cpp\
  Simulation/Harvest/HarvestWorkerList.cpp\
  Simulation/CommandList.cpp\
  Simulation/Event/EventStreamWriter.cpp\
  Simulation/Event/EventSubscriptionList.cpp\
  Simulation/Event/EventSystem.cpp\
  Simulation/Database.cpp\
  Animation/Animator.cpp\
  Animation/Registry.cpp\
  Rendering/Renderer.cpp\
  Rendering/WorldRenderer.cpp\
  Rendering/BoneMeshRegistry.cpp\
  Rendering/Programs.cpp\
  Rendering/BoneMeshDraws.cpp\
  Rendering/CommandStream.cpp\
  Rendering/DrawQueue.cpp\
  Rendering/Uniforms.cpp\
  Rendering/Buffers.cpp\
  Rendering/CullResult.cpp\
  Rendering/RenderTargets.cpp\
  Rendering/FullscreenQuad.cpp\
  Rendering/Textures.cpp\
  Rendering/StaticMeshes.cpp\
  Rendering/StaticMeshDraws.cpp\
  Rendering/MeshHelper.cpp\
  Rendering/Culler.cpp\
  Rendering/LightTransforms.cpp\
  Rendering/DrawSet.cpp\
  Rendering/BoneDrawSet.cpp\
  Rendering/StaticDrawSet.cpp\
  Rendering/PointLightDrawSet.cpp\
  Rendering/Frustum.cpp\
  Rendering/Shadow.cpp\
  Rendering/ShadowBlur.cpp\
  Rendering/ShadowBasePass.cpp\
  Rendering/MergePass.cpp\
  Rendering/GeometryPass.cpp\
  Rendering/SSAO.cpp\
  Rendering/SSAOGrainPass.cpp\
  Rendering/SSAOBlurPass.cpp\
  Rendering/DownsamplePass.cpp\
  Rendering/PointLights.cpp\
  Rendering/PointLightPass.cpp\
  Sys/GFX/OpenGL/Source/SysGFX.cpp\
  Sys/Net/Source/SysNet.cpp\
  $(PLATFORM_DIR)/Source/SysNet.cpp\
  $(PLATFORM_DIR)/Source/SysThread.cpp\
  $(PLATFORM_DIR)/Source/SysTime.cpp\
  $(PLATFORM_DIR)/Source/main.cpp
