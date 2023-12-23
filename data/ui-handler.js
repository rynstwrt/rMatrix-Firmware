const EFFECTS = [
    {
        id: "effect1",
        name: "Effect 1"
    },
    {
        id: "effect1",
        name: "Effect 1"
    },
    {
        id: "effect1",
        name: "Effect 1"
    },


    {
        id: "effect1",
        name: "Effect 1"
    },
    {
        id: "effect1",
        name: "Effect 1"
    },
    {
        id: "effect1",
        name: "Effect 1"
    }
];


const main = document.querySelector("main");


function createButtons()
{
    for (const effect of EFFECTS)
    {
        const button = document.createElement("button");
        button.textContent = effect.name;
        button.value = effect.id;
        main.appendChild(button);
    }
}
createButtons();