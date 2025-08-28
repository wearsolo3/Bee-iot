document.addEventListener("DOMContentLoaded", () => {
  const humidityDisplay = document.getElementById("humidity-display");
  const currentHumidity = document.getElementById("current-humidity");

  // Fetch humidity data from ESP32 server
  async function fetchHumidity() {
    try {
      const response = await fetch("http://192.168.1.138/sensor"); // Updated IP address
      if (!response.ok) {
        throw new Error(`Failed to fetch data: ${response.status} ${response.statusText}`);
      }
      const data = await response.json();
      if (data.humidity !== undefined) {
        humidityDisplay.textContent = `${data.humidity.toFixed(2)}%`;
        currentHumidity.textContent = `${data.humidity.toFixed(2)}%`;
      } else {
        throw new Error("Invalid data format");
      }
    } catch (error) {
      humidityDisplay.textContent = "Error fetching data";
      currentHumidity.textContent = "--%";
      console.error("Error:", error);
    }
  }

  // Fetch humidity every 5 seconds
  setInterval(fetchHumidity, 5000);
  fetchHumidity(); // Initial fetch
});
