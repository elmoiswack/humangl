#include "../includes/Window.hpp"

void Window::initButtons(int width, int height) {
	this->buttons.emplace_back(Button(ButtonType::UNCLICKABLE, 285, 20, 230, 60, width, height));
	GLTtext* screenName = gltCreateText();
	gltSetText(screenName, "Settings");
	this->buttonLabels.push_back(screenName);

	this->buttons.emplace_back(Button(ButtonType::WORD, 150, 100, 110, 40, width, height));
	GLTtext* bodyText = gltCreateText();
	gltSetText(bodyText, "Body");
	this->buttonLabels.push_back(bodyText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 450, 100, 120, 40, width, height));
	GLTtext* colorText = gltCreateText();
	gltSetText(colorText, "Color");
	this->buttonLabels.push_back(colorText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 150, 200, 110, 40, width, height));
	GLTtext* headText = gltCreateText();
	gltSetText(headText, "Head");
	this->buttonLabels.push_back(headText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 450, 200, 120, 40, width, height));
	GLTtext* torsoText = gltCreateText();
	gltSetText(torsoText, "Torso");
	this->buttonLabels.push_back(torsoText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 150, 300, 110, 40, width, height));
	GLTtext* leftText = gltCreateText();
	gltSetText(leftText, "Left");
	this->buttonLabels.push_back(leftText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 450, 300, 120, 40, width, height));
	GLTtext* rightText = gltCreateText();
	gltSetText(rightText, "Right");
	this->buttonLabels.push_back(rightText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 150, 400, 120, 40, width, height));
	GLTtext* upperText = gltCreateText();
	gltSetText(upperText, "Upper"); 
	this->buttonLabels.push_back(upperText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 450, 400, 120, 40, width, height));
	GLTtext* lowerText = gltCreateText();
	gltSetText(lowerText, "Lower");
	this->buttonLabels.push_back(lowerText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 150, 500, 90, 40, width, height));
	GLTtext* armText = gltCreateText();
	gltSetText(armText, "Arm");
	this->buttonLabels.push_back(armText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 450, 500, 90, 40, width, height));
	GLTtext* legText = gltCreateText();
	gltSetText(legText, "Leg");
	this->buttonLabels.push_back(legText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 120, 600, 120, 40, width, height));
	GLTtext* widthText = gltCreateText();
	gltSetText(widthText, "Width");
	this->buttonLabels.push_back(widthText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 300, 600, 130, 40, width, height));
	GLTtext* heightText = gltCreateText();
	gltSetText(heightText, "Height");
	this->buttonLabels.push_back(heightText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 480, 600, 120, 40, width, height));
	GLTtext* depthText = gltCreateText();
	gltSetText(depthText, "Depth");
	this->buttonLabels.push_back(depthText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 120, 700, 120, 40, width, height));
	GLTtext* rText = gltCreateText();
	gltSetText(rText, "Red");
	this->buttonLabels.push_back(rText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 300, 700, 130, 40, width, height));
	GLTtext* gText = gltCreateText();
	gltSetText(gText, "Green");
	this->buttonLabels.push_back(gText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 480, 700, 120, 40, width, height));
	GLTtext* bText = gltCreateText();
	gltSetText(bText, "Blue");
	this->buttonLabels.push_back(bText);

	this->buttons.emplace_back(Button(ButtonType::MINUS, 270, 800, 80, 80, width, height));
	GLTtext* minusText = gltCreateText();
	gltSetText(minusText, "-");
	this->buttonLabels.push_back(minusText);

	this->buttons.emplace_back(Button(ButtonType::PLUS, 450, 800, 80, 80, width, height));
	GLTtext* plusText = gltCreateText(); 
	gltSetText(plusText, "+");
	this->buttonLabels.push_back(plusText);	
}

bool Window::checkIfButtonPressed(float x, float y, BodyParts& body, std::vector<Mesh>& meshes) {
	for (std::size_t i = 1; i < buttons.size(); i++) {
		if (buttons[i].checkOnClick(x, y) == 1) {
			if ((buttons[i].getType() == ButtonType::PLUS) || (buttons[i].getType() == ButtonType::MINUS)) {
				return this->checkStruct(buttons[i].getType(), body, meshes);
			} else {
				this->updateStruct(i);
			}
			break ;
		}
	}
	return false;
}

bool Window::checkStruct(ButtonType type, BodyParts& body, std::vector<Mesh>& meshes) {
    BodyPartsIndex part = getSelectedPart();

    if (part == static_cast<BodyPartsIndex>(-1))
        return false;

    return modifyPart(part, type, body, meshes);
}

BodyPartsIndex Window::getSelectedPart() {
    if (selectedButtons.head)
		return BodyPartsIndex::HEAD;

    if (selectedButtons.torso) 
        return BodyPartsIndex::TORSO;

    if (selectedButtons.left && selectedButtons.upper && selectedButtons.arm)
        return BodyPartsIndex::LEFTUPARM;

    if (selectedButtons.left && selectedButtons.lower && selectedButtons.arm)
        return BodyPartsIndex::LEFTLOWARM;

    if (selectedButtons.right && selectedButtons.upper && selectedButtons.arm)
        return BodyPartsIndex::RIGHTUPARM;

    if (selectedButtons.right && selectedButtons.lower && selectedButtons.arm)
        return BodyPartsIndex::RIGHTLOWARM;

    if (selectedButtons.left && selectedButtons.upper && selectedButtons.leg)
        return BodyPartsIndex::LEFTUPLEG;

    if (selectedButtons.left && selectedButtons.lower && selectedButtons.leg)
        return BodyPartsIndex::LEFTLOWLEG;

    if (selectedButtons.right && selectedButtons.upper && selectedButtons.leg)
        return BodyPartsIndex::RIGHTUPLEG;

    if (selectedButtons.right && selectedButtons.lower && selectedButtons.leg)
        return BodyPartsIndex::RIGHTLOWLEG;

    return static_cast<BodyPartsIndex>(-1);
}

bool Window::modifyPart(BodyPartsIndex part, ButtonType type, BodyParts& body, std::vector<Mesh>& meshes) {
    if (selectedButtons.body)
    {
        if (selectedButtons.width) {
            if (type == ButtonType::PLUS)
               	body.updateWidth(part, 0.01);
            else
                body.updateWidth(part, -0.01);
        } 
		else if (selectedButtons.height) {
            if (type == ButtonType::PLUS)
                body.updateHeight(part, 0.01);
            else
                body.updateHeight(part, -0.01);
        }
        else if (selectedButtons.depth) {
            if (type == ButtonType::PLUS)
                body.updateDepth(part, 0.01);
            else
                body.updateDepth(part, -0.01);
        }
        return true;
    } else if (selectedButtons.color) {
        if (selectedButtons.red) {
            if (type == ButtonType::PLUS)
                this->updateMeshColor(meshes[part], 0, 0.05);
            else
                this->updateMeshColor(meshes[part], 0, -0.05);
        }
        else if (selectedButtons.green) {
            if (type == ButtonType::PLUS)
                this->updateMeshColor(meshes[part], 1, 0.05);
            else
                this->updateMeshColor(meshes[part], 1, -0.05);
        }
        else if (selectedButtons.blue) {
            if (type == ButtonType::PLUS)
                this->updateMeshColor(meshes[part], 2, 0.05);
            else
                this->updateMeshColor(meshes[part], 2, -0.05);
        }
    }
	return false;
}

void Window::updateMeshBody(BodyParts& body) {
	auto& parts = body.getBody();
	for (std::size_t i = 0; i < parts.size(); i++) {
		this->meshes[i].updateVBO(parts[i]);
	}
}

void Window::updateMeshColor(Mesh& mesh, int colorIndex, float value) {
	auto colors = mesh.getColor();
	colors[colorIndex] += value;
	if (colors[colorIndex] > 1.0f)
		colors[colorIndex] = 1.0f;
	if (colors[colorIndex] < 0.0f)
		colors[colorIndex] = 0.0f;
	mesh.updateColor(colors);
}

void Window::updateStruct(std::size_t i) {
	switch (i)
	{
	case ButtonOrder::BODY:
		this->selectedButtons.body = true;
		this->selectedButtons.color = false;
		break;
	case ButtonOrder::COLOR:
		this->selectedButtons.body = false;
		this->selectedButtons.color = true;
		break;
	case ButtonOrder::HEADINDEX:
		this->selectedButtons.head = true;
		this->selectedButtons.torso = false;
		this->selectedButtons.left = false;
		this->selectedButtons.right = false;
		this->selectedButtons.upper = false;
		this->selectedButtons.lower = false;
		this->selectedButtons.arm = false;
		this->selectedButtons.leg = false;
		break ;
	case ButtonOrder::TORSOINDEX:
		this->selectedButtons.head = false;
		this->selectedButtons.torso = true;
		this->selectedButtons.left = false;
		this->selectedButtons.right = false;
		this->selectedButtons.upper = false;
		this->selectedButtons.lower = false;	
		this->selectedButtons.arm = false;
		this->selectedButtons.leg = false;
		break ;
	case ButtonOrder::LEFT:
		this->selectedButtons.left = true;
		this->selectedButtons.right = false;
		this->selectedButtons.head = false;
		this->selectedButtons.torso = false;
		break;
	case ButtonOrder::RIGHT:
		this->selectedButtons.left = false;
		this->selectedButtons.right = true;
		this->selectedButtons.head = false;
		this->selectedButtons.torso = false;
		break;
	case ButtonOrder::UPPER:
		this->selectedButtons.upper = true;
		this->selectedButtons.lower = false;
		this->selectedButtons.head = false;
		this->selectedButtons.torso = false;
		break;
	case ButtonOrder::LOWER:
		this->selectedButtons.upper = false;
		this->selectedButtons.lower = true;
		this->selectedButtons.head = false;
		this->selectedButtons.torso = false;
		break;
	case ButtonOrder::ARM:
		this->selectedButtons.arm = true;
		this->selectedButtons.leg = false;
		this->selectedButtons.head = false;
		this->selectedButtons.torso = false;
		break;
	case ButtonOrder::LEG:
		this->selectedButtons.arm = false;
		this->selectedButtons.leg = true;
		this->selectedButtons.head = false;
		this->selectedButtons.torso = false;
		break;
	case ButtonOrder::WIDTH:
		this->selectedButtons.width = true;
		this->selectedButtons.height = false;
		this->selectedButtons.depth = false;
		this->selectedButtons.red = false;
		this->selectedButtons.green = false;
		this->selectedButtons.blue = false;
		break;
	case ButtonOrder::HEIGHT:
		this->selectedButtons.width = false;
		this->selectedButtons.height = true;
		this->selectedButtons.depth = false;
		this->selectedButtons.red = false;
		this->selectedButtons.green = false;
		this->selectedButtons.blue = false;
		break;
	case ButtonOrder::DEPTH:
		this->selectedButtons.width = false;
		this->selectedButtons.height = false;
		this->selectedButtons.depth = true;
		this->selectedButtons.red = false;
		this->selectedButtons.green = false;
		this->selectedButtons.blue = false;
		break;
	case ButtonOrder::RED:
		this->selectedButtons.red = true;
		this->selectedButtons.green = false;
		this->selectedButtons.blue = false;
		this->selectedButtons.width = false;
		this->selectedButtons.height = false;
		this->selectedButtons.depth = false;
		break;
	case ButtonOrder::GREEN:
		this->selectedButtons.red = false;
		this->selectedButtons.green = true;
		this->selectedButtons.blue = false;
		this->selectedButtons.width = false;
		this->selectedButtons.height = false;
		this->selectedButtons.depth = false;
		break;
	case ButtonOrder::BLUE:
		this->selectedButtons.red = false;
		this->selectedButtons.green = false;
		this->selectedButtons.blue = true;
		this->selectedButtons.width = false;
		this->selectedButtons.height = false;
		this->selectedButtons.depth = false;
		break;
	default:
		break;
	}
	this->checkButtonCounterpart(i);
}

void Window::checkButtonCounterpart(std::size_t index) {
	// if (index >= ButtonOrder::WIDTH && index <= ButtonOrder::BLUE) {
	// 	for (std::size_t i = ButtonOrder::WIDTH; i <= ButtonOrder::BLUE; i++) {
	// 		if (i == index)
	// 			continue;
	// 		else
	// 			this->buttons[i].deactivateButton();
	// 	}
	// } else if (index % 2 == 0) {
	// 	if (this->buttons[index - 1].getActive() == true)
	// 		this->buttons[index - 1].deactivateButton();
	// } else {
	// 	if (this->buttons[index + 1].getActive() == true)
	// 		this->buttons[index + 1].deactivateButton();
	// }
	for (std::size_t i = 0; i < this->buttons.size(); i++) {
		
	}
}