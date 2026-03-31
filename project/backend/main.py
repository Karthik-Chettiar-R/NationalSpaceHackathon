from fastapi import FastAPI
from pydantic import BaseModel
from models.Telemetry import Telemetry 
from models.Maneuver import Maneuver
from typing import Dict, Any
from models.SimulationStep import SimulationStep
import physicsEngine

app = FastAPI()


@app.post("/api/telemetry")
def telemetry(data:Telemetry):
    telemetry_data = data
    x=telemetry_data.objects[0].r.x
    y=telemetry_data.objects[0].r.y
    z=telemetry_data.objects[0].r.z

    return physicsEngine.acceleration([x, y, z])

@app.post("/api/maneuver/schedule")
def schedule_maneuver(data: Maneuver):
    maneuver_data=data
    print(maneuver_data)
    return {'maneuver_data': maneuver_data}

@app.post("/api/simulate/step")
def simulate_step(data: SimulationStep):
    print(data)
    return {'simulation_step': data}