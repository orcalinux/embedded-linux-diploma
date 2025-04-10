const ledSelect = document.getElementById("ledSelect");
const ledMessage = document.getElementById("ledMessage");

async function setLedState(state) {
  try {
    const ledNumber = ledSelect.value; // "0", "1", or "2" as string
    const url = `/led/${ledNumber}/state/${state}`;
    const response = await fetch(url);
    const data = await response.json();

    if (data.error) {
      ledMessage.textContent = `Error: ${data.error}`;
      ledMessage.style.color = "red";
    } else {
      ledMessage.textContent = `LED ${data.led} state: ${
        data.state === 1 ? "ON" : "OFF"
      }`;
      ledMessage.style.color = "green";
    }
  } catch (err) {
    console.error("Error:", err);
    ledMessage.textContent = "Error toggling LED.";
    ledMessage.style.color = "red";
  }
}

function turnLedOn() {
  setLedState(1);
}

function turnLedOff() {
  setLedState(0);
}
