#include "header/RBO.h"

RBO::RBO(int width, int height) {
	glGenRenderbuffers(1, &id);
	bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void RBO::bind() {
	glBindRenderbuffer(GL_RENDERBUFFER, id);
}

void RBO::unbind() {
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RBO::destroy() {
	glDeleteRenderbuffers(1, &id);
}