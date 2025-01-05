import pandas as pd
import plotly.graph_objects as go

landing_trajectory = pd.read_csv("./trajectory_data.csv")
drag_trajectory = pd.read_csv("./trajectory_with_drag.csv")

x_landing = landing_trajectory["x"]
y_landing = landing_trajectory["y"]

x_drag = drag_trajectory["x"]
y_drag = drag_trajectory["y"]

offset = 1000 
y_drag_offset = y_drag + offset

fig = go.Figure()

fig.add_trace(go.Scatter(x=x_landing, y=y_landing, mode='markers+lines', name="Landing Trajectory", line=dict(color='blue')))

fig.add_trace(go.Scatter(x=x_drag, y=y_drag_offset, mode='markers+lines', name="Trajectory with Drag", line=dict(color='red')))

fig.update_layout(
    title="Landing vs Drag Trajectories",
    xaxis_title="Distance",
    yaxis_title="Altitude",
    showlegend=True
)

fig.show()
