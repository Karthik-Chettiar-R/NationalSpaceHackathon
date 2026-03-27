from pydantic import BaseModel

class SimulationStep(BaseModel):
    step_seconds:int