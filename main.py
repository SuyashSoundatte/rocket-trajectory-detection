import pandas as pd
import plotly.graph_objects as go

trajectory_data = pd.read_csv("./trajectory_data.csv")

x_values = trajectory_data["x"]
y_values = trajectory_data["y"]

fig = go.Figure()

fig.add_trace(go.Scatter(x=x_values, y=y_values, mode='markers+lines', name="Trajectory"))

fig.update_layout(
    title="Trajectory Points",
    xaxis_title="X Coordinate",
    yaxis_title="Y Coordinate",
    showlegend=True
)

fig.show()
