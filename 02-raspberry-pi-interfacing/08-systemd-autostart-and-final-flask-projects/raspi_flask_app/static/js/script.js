const statusElem = document.getElementById("buttonStatus");
const refreshBtn = document.getElementById("refreshBtn");

async function getButtonStatus() {
  try {
    const response = await fetch("/push-button");
    const data = await response.json(); // { pressed: true/false }
    if (data.pressed) {
      statusElem.textContent = "Button is pressed";
      statusElem.style.color = "red";
    } else {
      statusElem.textContent = "Button is not pressed";
      statusElem.style.color = "green";
    }
  } catch (err) {
    console.error("Error:", err);
    statusElem.textContent = "Error fetching button status";
    statusElem.style.color = "gray";
  }
}

// If the elements exist on this page, add event listener
if (refreshBtn) {
  refreshBtn.addEventListener("click", getButtonStatus);
}
// Optionally auto-update every 2 seconds
// setInterval(getButtonStatus, 2000);

// On page load, fetch status initially
window.addEventListener("load", getButtonStatus);
