from pydantic import BaseModel
from models.Telemetry import Vector

class Vector(BaseModel):
    x:float
    y:float
    z:float

class Burn(BaseModel):
    burn_id:str
    burnTime:str
    deltaV_vector:Vector

class Maneuver(BaseModel):
    satelliteId:str
    maneuver_sequence:list[Burn]
