from fastapi import FastAPI
from pydantic import BaseModel
from models.Telemetry import Telemetry 
from models.Maneuver import Maneuver
from typing import Dict, Any
from models.SimulationStep import SimulationStep
app = FastAPI()


@app.post("/api/telemetry")
def telemetry(data:Telemetry):
    telemetry_data = data
    print(telemetry_data)
    return {'telemetry_data ': telemetry_data}

@app.post("/api/maneuver/schedule")
def schedule_maneuver(data: Maneuver):
    maneuver_data=data
    print(maneuver_data)
    return {'maneuver_data': maneuver_data}

@app.post("/api/simulate/step")
def simulate_step(data: SimulationStep):
    print(data)
    return {'simulation_step': data}