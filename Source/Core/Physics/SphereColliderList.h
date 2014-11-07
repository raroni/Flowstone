namespace Physics {
  template<typename Handle, typename BodyIndex>
  class SphereColliderList {
    const static uint8_t maxCount = 128;
    float radii[maxCount];
    BodyIndex bodyIndices[maxCount];
    uint8_t indices[128];
    uint8_t ids[128];
    uint8_t count = 0;
    FreeList idPool;
  public:
    Handle create(BodyIndex body, float radius) {
      radii[count] = radius;
      bodyIndices[count] = body;
      Handle handle;
      handle.id = idPool.obtain();
      ids[count] = handle.id;
      indices[handle.id] = count;
      count++;
      return handle;
    }
    void destroy(Handle handle) {
      uint8_t destroyIndex = indices[handle.id];
      uint8_t lastIndex = count-1;
      radii[destroyIndex] = radii[lastIndex];
      bodyIndices[destroyIndex] = bodyIndices[lastIndex];
      indices[ids[lastIndex]] = destroyIndex;
      count--;
      idPool.free(handle.id);
    }
    const float* getRadii() const {
      return radii;
    }
    uint8_t getCount() {
      return count;
    }
    const BodyIndex* getBodyIndices() const {
      return bodyIndices;
    }
  };
}
