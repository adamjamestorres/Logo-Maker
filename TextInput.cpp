//
// Created by Adam Torres on 5/30/21.
//

#include "TextInput.h"
/**
 * Constructor that calls all the helper functions needed for this class and sets the label for the text box
 * @param labelText is the label that will be displayed to the left of the text box when on the SFML window
 */
TextInput::TextInput(std::string labelText, float rows, float charactersWide)
        : maxRows(rows), currentRow(1)
{
    AssignComponentID();
    LoadFontFromFile();
    InitializeInputField(rows, charactersWide);
    InitializeLabel(labelText);
    InitializeTextProperties();
    AssignCursorPosition();
}

/**
 * Draws the text box label, text box, keyboard input, and the text cursor
 * @param window that the TextInput object is drawn onto
 * @param states allows global transform on top of each objects transform
 */
void TextInput::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(label);
    window.draw(inputField, states);
    for (auto& itr : textList) { window.draw(itr); }
    textCursor.draw(window, states);
}

/**
 * Creates blinking cursor if mouse clicks into input field.
 * Check object has been enabled
 * @param window processes SFML events
 * @param event holds all the information about the system
 */
void TextInput::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    if (LeftClickedInsideTextBox(event, window))
    {
        return;
    }
    if (IsNotEnabled())
    {
        return;
    }
    ProcessEnteredText(event);
}

/**
 * Called the text cursor class update to be updated in the text input class
 */
void TextInput::update()
{
    textCursor.update();
}

/**
 * Takes a snapshot
 */
void TextInput::takeSnapshot()
{
    std::list<sf::Text> listCopy = textList;
    std::shared_ptr<TextBoxSnapShot> snapPtr = std::make_shared<TextBoxSnapShot>(componentID, listCopy);
    History::pushHistory(snapPtr);
}

/**
 * Applies a snapshot
 */
void TextInput::applySnapshot(const std::shared_ptr<SnapShot> snapshot)
{
    this->textList = std::static_pointer_cast<TextBoxSnapShot>(snapshot)->GetTextList();
    AssignCursorPosition();
}

/**
 * Set position using SFML member functions from various SFML classes
 * @param pos x and y coordinate float
 */
void TextInput::setPosition(sf::Vector2f pos)
{
    sf::Vector2f difPos = sf::Vector2f(pos.x - inputField.getPosition().x, pos.y - inputField.getPosition().y);

    inputField.setPosition(pos);
    label.setPosition(inputField.getPosition().x - 150.f, inputField.getPosition().y);
    templateText.setPosition(inputField.getPosition().x + 5, inputField.getPosition().y + 2);
    for (auto& itr : textList)
    {
        itr.move(difPos);
    }
    AssignCursorPosition();
}

/**
 * Uses the memory address of the object to assign the component ID
 */
void TextInput::AssignComponentID()
{
    std::ostringstream getAddress;
    getAddress << this;
    componentID = getAddress.str();
    History::addComponent(componentID, this);
}

/**
 * Loads font from the file
 */
void TextInput::LoadFontFromFile()
{
    if (!font.loadFromFile("../Fonts/OpenSans-Bold.ttf"))
    {
        std::cout << "Error, failed to load fonts \n";
    }
}

/**
 * Initializes an text input field aka text box
 */
void TextInput::InitializeInputField(float rows, float charactersWide)
{
    inputField.setFillColor(sf::Color::Transparent);
    inputField.setOutlineColor(sf::Color::White);
    inputField.setOutlineThickness(2.0);
    inputField.setSize(sf::Vector2f(charactersWide * 6.f, rows * 22.f + 13.f));
    inputField.setPosition(sf::Vector2f(200.0, 50.0));
}

/**
 * Initializes the template text
 */
void TextInput::InitializeTextProperties()
{
    templateText.setFont(font);
    templateText.setString("");
    templateText.setPosition(inputField.getPosition().x + 5, inputField.getPosition().y + 2);
    templateText.setFillColor(sf::Color::White);
    templateText.setCharacterSize(20);
}

/**
 * Initializes the input field label
 * @param labelText to be displayed onto the SFML window
 */
void TextInput::InitializeLabel(std::string labelText)
{
    label.setFont(font);
    label.setString(labelText);
    label.setPosition(inputField.getPosition().x - 150.f, inputField.getPosition().y);
    label.setFillColor(sf::Color::White);
    label.setCharacterSize(20);
}

/**
 * Using SFML member functions from SFML classes to assign cursor position to the left of text
 */
void TextInput::AssignCursorPosition()
{
    if (textList.empty())
    {
        textCursor.SetPosition(sf::Vector2f(templateText.getPosition().x + templateText.getGlobalBounds().width, templateText.getPosition().y));
    }
    else
    {
        textCursor.SetPosition(sf::Vector2f(textList.back().getPosition().x + textList.back().getGlobalBounds().width + textList.back().getLetterSpacing(), textList.back().getPosition().y));
    }

    //Must be its own if and calculate after cursor is set to check if cursor has exceeded bounds
    if (textCursor.GetPosition().x > inputField.getPosition().x + inputField.getGlobalBounds().width - 10.0f && currentRow < maxRows)
    {
        textCursor.SetPosition(sf::Vector2f(templateText.getPosition().x, textList.back().getPosition().y + 22));
    }

    setCurrentRow();
}

void TextInput::AssignCursorPosition(sf::Vector2f position)
{
    textCursor.SetPosition(position);
    setCurrentRow();
}

/**
 * Creates a blinking Cursor when the left mouse button is clicked in the input field box
 * @param event holds all the information about the system
 * @param window that Text cursor blinks on
 * @return Is true blinking occurs, if false then there is no blinking
 */
bool TextInput::LeftClickedInsideTextBox(sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
            if (inputField.getGlobalBounds().contains(mousePos))
            {
                textCursor.SetEnabled();
                EnableState(ObjectState::ENABLED);
                return true;
            }
            textCursor.SetDisabled();
            this->DisableState(ObjectState::ENABLED);
        }
    }
    return false;
}

/**
 * If text is being typed, first check if undo short cut is being pressed.
 * Then check if delete button is being pressed, if pressed then removed that character from the
 * linked list and make sure the string does not need to be colored.
 * If these two situations are not occurring then key board input get displayed and pushed into the linked list
 * snapshots are taken and ready to be used for undo functionality
 * @param event holds all the information about the system
 */
void TextInput::ProcessEnteredText(sf::Event& event)
{
    if (event.type == sf::Event::TextEntered)
    {
        if (isUndoInput(event)) { return; }

        if (event.text.unicode == 13)
        {
            if (textList.empty()) { return; }
            if (currentRow == maxRows) { return; }

            AssignCursorPosition(sf::Vector2f(templateText.getPosition().x + templateText.getGlobalBounds().width, textList.back().getPosition().y + 22));
            return;
        }

        if (event.text.unicode == 32) { //if spacebar is pressed, it stores that list object iterator as a word break
            setSpaceItr();
        }

        if (event.text.unicode == 8) // if backspace key is pressed, the word break iterator needs recalculated and is done through findLastSpaceItr
        {
            if (textList.empty()) { return; }
            takeSnapshot();
            textList.pop_back();
            findLastSpaceItr();
            keywordCompare.Evaluate(textList);
        }
        else
        {
            bool useNextRow = false;
            sf::String stringBuffer = event.text.unicode;
            sf::Text bufferText = templateText;
            bufferText.setString(stringBuffer);
            if (!textList.empty())
            {
                bufferText.setPosition(textCursor.GetPosition().x + 3, textCursor.GetPosition().y);

                if (willOverflow(bufferText) && currentRow < maxRows) { useNextRow = true; } //Checks if we can overflow to next line
                else if (willOverflow(bufferText)) { return; } //or if we should halt accepting input
            }
            takeSnapshot();
            textList.push_back(bufferText);
            keywordCompare.Evaluate(textList);
            if (useNextRow) { moveToNextRow(); }
        }
        AssignCursorPosition();
    }

}

/**
 * Checks if control + z is pressed
 * @param event holds all the information about the system
 * @return true if control + z pressed, else false
 */
bool TextInput::isUndoInput(sf::Event& event)
{
    if (event.text.unicode == 26) {
        findLastSpaceItr();
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Does not allow the text input to exceed the input field box
 * @param text that is being typed onto the SFML screen
 * @return true text will overflow, else false
 */
bool TextInput::willOverflow(sf::Text text)
{
    float paddingVal = 10.0f;

    if (textCursor.GetPosition().x + text.getGlobalBounds().width > inputField.getPosition().x + inputField.getGlobalBounds().width - paddingVal)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void TextInput::setCurrentRow()
{
    currentRow = (textCursor.GetPosition().y - inputField.getPosition().y) / 22 + 1;
}

void TextInput::setSpaceItr()
{
    if (textList.empty()) { return; }
    spaceItr = textList.begin();
    std::advance(spaceItr, textList.size() - 1);
}

void TextInput::findLastSpaceItr()
{
    std::list<sf::Text>::iterator itr = textList.begin();
    spaceItr = textList.begin();

    while (itr != textList.end())
    {
        if (itr->getString() == " ")
        {
            spaceItr = itr;
        }

        itr++;
    }
}

void TextInput::moveToNextRow()
{
    if (spaceItr == textList.end() || spaceItr == textList.begin()) { return; } //Prevents runtime error if we have a line overflow without a word break or if
    //The last character prior to the bounding area is a space

    std::list<sf::Text>::iterator leadITR = spaceItr;
    std::list<sf::Text>::iterator trailingITR;

    std::advance(leadITR, 2);

    if (leadITR == textList.end()) { return; } //Checks if the advance leads to the end of the list so as not to dereference an endlist iterator

    //Sets initial position for first letter
    leadITR->setPosition(templateText.getPosition().x, leadITR->getPosition().y+22);
    trailingITR = leadITR++;
    //Follows through with the rest of the word
    while (leadITR != textList.end())
    {
        leadITR->setPosition(trailingITR->getPosition().x + trailingITR->getGlobalBounds().width + textList.back().getLetterSpacing(), trailingITR->getPosition().y);
        trailingITR = leadITR++;
    }
}

/**
 * Checks text input object status
 * @return true for not enable, else false
 */
bool TextInput::IsNotEnabled()
{
    return !this->CheckStateStatus(ObjectState::ENABLED);
}

/**
 * Set the label that is placed to the left of the input field
 * @param labelText is what the label gets set to
 */
void TextInput::setLabel(std::string labelText) {
    label.setString(labelText);
}

/**
 * Uses SFML getPosition from rectangle class to get position of the text box
 * @return position of the inputField also known as text box
 */
sf::Vector2f TextInput::getPosition() {
    return inputField.getPosition();
}

std::string TextInput::getTextString()
{
    if (textList.empty()) { return ""; }

    sf::String str;

    for (auto& itr : textList)
    {
        str += itr.getString();
    }

    return str;
}

void TextInput::setTextString(std::string str)
{
    textList.clear();
    AssignCursorPosition();
    findLastSpaceItr();

    if (str.empty()) { return; }

    int index = 0;

    while (index < str.length())
    {
        sf::String stringBuffer = str[index];
        sf::Text bufferText = templateText;
        bufferText.setString(stringBuffer);

        if (!textList.empty())
        {
            bufferText.setPosition(textCursor.GetPosition().x + 3, textCursor.GetPosition().y);

            if (willOverflow(bufferText)) { return; } //or if we should halt accepting input
        }
        textList.push_back(bufferText);
        keywordCompare.Evaluate(textList);

        AssignCursorPosition();

        index++;
    }

    findLastSpaceItr();
}