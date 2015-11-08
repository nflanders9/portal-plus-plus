#include "game_object.h"

GameObject::GameObject(int height, int width, Posn & p) {
	m_height = height;
	m_width = width;
	m_pos = p;
	image_name = "";
}

GameObject::GameObject(GameObject & o) {

}

void GameObject::setImage(string s) {
	this->image_name = s;
}

int GameObject::getWidth() {
	return m_width;
}

int GameObject::getHeight() {
	return m_height;
}

Posn GameObject::getPosn() {
	return m_pos;
}

bool operator==(const GameObject & g1, const GameObject & g2) {
	return g1.m_width == g2.m_width && g1.m_height == g2.m_height && g1.m_pos == g2.m_pos && g1.image_name == g2.image_name;
}

bool operator!=(const GameObject & g1, const GameObject & g2) {
	return !(g1 == g2);
}

bool GameObject::hasCollided(GameObject & g) {
	return false;
}

void GameObject::move(Velocity v) {
	//TODODTODODODODO
}