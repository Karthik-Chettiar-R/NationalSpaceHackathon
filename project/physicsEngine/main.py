import physicsEngine
from fastapi import FastAPI

app=FastAPI()

@app.post("/api/position")
def position(data):
    return physicsEngine.acceleration([data.x, data.y, data.z])
