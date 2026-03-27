from pydantic import BaseModel 

class Vector(BaseModel):
    x:float
    y:float
    z:float

class SpaceObject(BaseModel):
    id:str
    type:str
    r:Vector
    v:Vector

class Telemetry(BaseModel):
    timestamp:str
    objects:list[SpaceObject]