import pandas as pd
import numpy as np
import plotly.graph_objects as go

# Constants for WGS84 ellipsoid
a = 6378137.0  # Semi-major axis in meters
f = 1 / 298.257223563  # Flattening
b = a * (1 - f)  # Semi-minor axis

def geodetic_to_ecef(lat, lon, alt):
    """
    Convert geodetic coordinates (latitude, longitude, altitude) to ECEF coordinates.
    :param lat: Latitude in degrees
    :param lon: Longitude in degrees
    :param alt: Altitude in meters
    :return: ECEF coordinates (x, y, z)
    """
    # Convert lat/lon to radians
    lat_rad = np.radians(lat)
    lon_rad = np.radians(lon)

    # Compute prime vertical radius of curvature
    N = a / np.sqrt(1 - (1 - (b / a) ** 2) * np.sin(lat_rad) ** 2)

    # Calculate ECEF coordinates
    x = (N + alt) * np.cos(lat_rad) * np.cos(lon_rad)
    y = (N + alt) * np.cos(lat_rad) * np.sin(lon_rad)
    z = (b**2 / a**2 * N + alt) * np.sin(lat_rad)

    return x, y, z

# Load trajectory data from a CSV file
# Ensure the CSV has columns: "lat", "lon", "alt"
csv_file_path = "./trajectory_data.csv"  # Replace with your CSV file path
trajectory_data = pd.read_csv(csv_file_path)

# Convert trajectory points to ECEF
ecef_trajectory = [
    geodetic_to_ecef(row["lat"], row["lon"], row["alt"])
    for _, row in trajectory_data.iterrows()
]
x_vals, y_vals, z_vals = zip(*ecef_trajectory)

# Generate WGS84 ellipsoid surface points
u = np.linspace(0, 2 * np.pi, 100)
v = np.linspace(0, np.pi, 100)
x_ellipsoid = a * np.outer(np.cos(u), np.sin(v))
y_ellipsoid = a * np.outer(np.sin(u), np.sin(v))
z_ellipsoid = b * np.outer(np.ones_like(u), np.cos(v))

# Flatten ellipsoid points for Plotly
x_ellipsoid_flat = x_ellipsoid.flatten()
y_ellipsoid_flat = y_ellipsoid.flatten()
z_ellipsoid_flat = z_ellipsoid.flatten()

# Create the Earth surface plot
earth_surface = go.Mesh3d(
    x=x_ellipsoid_flat,
    y=y_ellipsoid_flat,
    z=z_ellipsoid_flat,
    color='blue',
    opacity=0.5,
    name="Earth",
)

# Create the rocket trajectory plot
trajectory_plot = go.Scatter3d(
    x=x_vals,
    y=y_vals,
    z=z_vals,
    mode="lines+markers",
    line=dict(color="red", width=4),
    marker=dict(size=5, color="red"),
    name="Rocket Trajectory",
)

# Combine into a single figure
fig = go.Figure(data=[earth_surface, trajectory_plot])

# Update layout for better visualization
fig.update_layout(
    title="Rocket Landing Trajectory on WGS84 Earth Model",
    scene=dict(
        xaxis_title="X (m)",
        yaxis_title="Y (m)",
        zaxis_title="Z (m)",
        aspectmode="data",
    ),
    legend=dict(x=0.1, y=0.9),
)

# Show the figure
fig.show()
