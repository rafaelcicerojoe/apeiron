#include "rbTree.h"


RBNode * rbtNewNode(int key){
	RBNode * n = (RBNode*)malloc(sizeof(RBNode));
	if(n != NULL){
		n->color = RED;
		n->key = key;
		n->left = NULL;
		n->right = NULL;
		n->parent = NULL;
		return n;
	}
	return NULL;
}


int rbtIsOnLeft(RBNode * node){
	return node == node->parent->left ? TRUE:FALSE;
}

RBNode * rbtUncle(RBNode * node){
    if(node->parent == NULL || node->parent->parent == NULL){
        return NULL;
    }
    if (rbtIsOnLeft(node->parent) == TRUE){
        return node->parent->parent->right;
    }
    else{
        return node->parent->parent->left;
    }
}

RBNode * rbtSibling(RBNode * node){
    if (node->parent == NULL){
        return NULL;
    }
    if (rbtIsOnLeft(node)){
        return node->parent->right;
    }
    return node->parent->left;
}

void rbtMoveDown(RBNode * node, RBNode * nParent){
  if (node->parent != NULL) {
    if (rbtIsOnLeft(node)) {
      node->parent->left = nParent;
    } else {
      node->parent->right = nParent;
    }
  }
  nParent->parent = node->parent;
  node->parent = nParent;
}

int rbtHasRedChild(RBNode * node) {
	return (node->left != NULL && node->left->color == RED) ||
           (node->right != NULL && node->right->color == RED) ? TRUE:FALSE;
}

RBNode * rbtSuccessor(RBNode * node) {
    RBNode * temp = node;
    while (temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

void rbtLeftRotate(RBNode ** rbt, RBNode * node){
	RBNode * nParent = node->right;
	if(node == *rbt){
		*rbt = nParent;
	}
	rbtMoveDown(node, nParent);
	node->right = nParent->left;
	if(nParent->left != NULL){
		nParent->left->parent = node;
	}
	nParent->left = node;
}

void rbtRightRotate(RBNode ** rbt, RBNode * node){
	RBNode * nParent = node->left;
	if(node == *rbt){
		*rbt = nParent;
	}
	rbtMoveDown(node, nParent);
	node->left = nParent->right;
	if(nParent->right != NULL){
		nParent->right->parent = node;
	}
	nParent->right = node;
}

void rbtSwapColors(RBNode * n1, RBNode * n2){
	char temp;
	temp = n1->color;
	n1->color = n2->color;
	n2->color = temp;
}

void rbtSwapValues(RBNode * n1, RBNode * n2){
	int temp;
	temp = n1->key;
	n1->key = n2->key;
	n2->key = temp;
}

void rbtFixRedRed(RBNode ** rbt, RBNode * node){
	if(node == *rbt){
		node->color = BLACK;
		return;
	}
	RBNode * parent = node->parent;
	RBNode * grandParent = parent->parent;
	RBNode * uncle = rbtUncle(node);
	if(parent->color != BLACK){
		if(uncle != NULL && uncle->color == RED){
			parent->color = BLACK;
			uncle->color = BLACK;
			grandParent->color = RED;
			rbtFixRedRed(rbt, grandParent);
		} else {
			if(rbtIsOnLeft(parent) == TRUE){
				if(rbtIsOnLeft(node) == TRUE){
					rbtSwapColors(parent, grandParent);
				} else {
					rbtLeftRotate(rbt, parent);
					rbtSwapColors(node, grandParent);
				}
				rbtRightRotate(rbt, grandParent);
			} else {
				if(rbtIsOnLeft(node) == TRUE){
					rbtRightRotate(rbt, parent);
					rbtSwapColors(node, grandParent);
				} else {
					rbtSwapColors(parent, grandParent);
				}
				rbtLeftRotate(rbt, grandParent);
			}
		}
	}
}

RBNode * rbtDeleteHelper(RBNode * node) {
    if (node->left != NULL && node->right != NULL){
        return rbtSuccessor(node->right);
    }
    if (node->left == NULL && node->right == NULL){
    	return NULL;
    }
    if (node->left != NULL){
        return node->left;
    } else {
        return node->right;
    }
}

void rbtFixDoubleBlack(RBNode ** rbt, RBNode * node) {
    if (node == *rbt){
        return;
    }
    RBNode * sibling = rbtSibling(node);
    RBNode * parent = node->parent;
    if (sibling == NULL) {
      rbtFixDoubleBlack(rbt, parent);
    } else {
      if (sibling->color == RED) {
        parent->color = RED;
        sibling->color = BLACK;
        if (rbtIsOnLeft(sibling)) {
          rbtRightRotate(rbt, parent);
        } else {
          rbtLeftRotate(rbt, parent);
        }
        rbtFixDoubleBlack(rbt, node);
      } else {
        if (rbtHasRedChild(sibling)) {
          if (sibling->left != NULL && sibling->left->color == RED) {
            if (rbtIsOnLeft(sibling)) {
              sibling->left->color = sibling->color;
              sibling->color = parent->color;
              rbtRightRotate(rbt, parent);
            } else {
              sibling->left->color = parent->color;
              rbtRightRotate(rbt, sibling);
              rbtLeftRotate(rbt, parent);
            }
          } else {
            if (rbtIsOnLeft(sibling)) {
              sibling->right->color = parent->color;
              rbtLeftRotate(rbt, sibling);
              rbtRightRotate(rbt, parent);
            } else {
              sibling->right->color = sibling->color;
              sibling->color = parent->color;
              rbtLeftRotate(rbt, parent);
            }
          }
          parent->color = BLACK;
        } else {
          sibling->color = RED;
          if (parent->color == BLACK)
            rbtFixDoubleBlack(rbt, parent);
          else
            parent->color = BLACK;
        }
      }
    }
 }

void rbtDeleteNode(RBNode ** rbt, RBNode * node) {
  RBNode * replaceNode = rbtDeleteHelper(node);
  int uvBlack = ((replaceNode == NULL || replaceNode->color == BLACK)
		  && (node->color == BLACK)) ? TRUE:FALSE;
  RBNode * parent = node->parent;
  if (replaceNode == NULL) {
    if (node == *rbt) {
      *rbt = NULL;
    } else {
      if (uvBlack == TRUE) {
        rbtFixDoubleBlack(rbt, node);
      } else {
        if (rbtSibling(node) != NULL)
          rbtSibling(node)->color = RED;
      }
      if (rbtIsOnLeft(node)) {
        parent->left = NULL;
      } else {
        parent->right = NULL;
      }
    }
    free(node);
    return;
  }
  if (node->left == NULL || node->right == NULL) {
    if (node == *rbt) {
      node->key = replaceNode->key;
      node->left = NULL;
      node->right = NULL;
      free(replaceNode);
    } else {
      if (rbtIsOnLeft(node)) {
        parent->left = replaceNode;
      } else {
        parent->right = replaceNode;
      }
      free(node);
      replaceNode->parent = parent;
      if (uvBlack == TRUE) {
        rbtFixDoubleBlack(rbt, replaceNode);
      } else {
        replaceNode->color = BLACK;
      }
    }
    return;
  }
  rbtSwapValues(replaceNode, node);
  rbtDeleteNode(rbt, replaceNode);
}

RBNode * rbtSearch(RBNode ** rbt, int key) {
  RBNode * temp = *rbt;
  while(temp != NULL){
    if(key < temp->key){
      if(temp->left == NULL){
          break;
      } else {
          temp = temp->left;
      }

    } else {
      if(temp->right == NULL){
          break;
      } else {
          temp = temp->right;
      }
    }
  }

  return temp;
}
void *Return_rbtSearch(RBNode ** rbt, int key) {
  RBNode * temp = *rbt;
  while(temp != NULL){
    if(key < temp->key){
      if(temp->left == NULL){
          break;
      } else {
          temp = temp->left;
      }
    } else if(key == temp->key){
      return temp->key;
      break;
    } else {
      if(temp->right == NULL){
          break;
      } else {
          temp = temp->right;
      }
    }
  }

  return NULL;
}
RBNode *Return_Node_rbtSearch(RBNode ** rbt, int key) {
  RBNode * temp = *rbt;
  while(temp != NULL){
    if(key < temp->key){
      if(temp->left == NULL){
          break;
      } else {
          temp = temp->left;
      }
    } else if(key == temp->key){
      return temp;
      break;
    } else {
      if(temp->right == NULL){
          break;
      } else {
          temp = temp->right;
      }
    }
  }

  return NULL;
}


int rbtInsert(RBNode ** rbt, int key){
  RBNode * newNode = rbtNewNode(key);
  if (*rbt == NULL) {
    newNode->color = BLACK;
    *rbt = newNode;
  } else {
    RBNode * temp = rbtSearch(rbt, key);
    if (temp->key == key) {
      return FALSE;
    }
    newNode->parent = temp;
    if (key < temp->key){
        temp->left = newNode;
    }
    else{
        temp->right = newNode;
    }
    rbtFixRedRed(rbt, newNode);
  }
  return TRUE;
}

RBNode *RB_FILE_Insert(int dados){
  RBNode *t = NULL;
   FILE *arq;
    if(dados == 1){
        arq = fopen("dados/file1000.txt","r");
    }else if(dados == 2){
        arq = fopen("dados/file5000.txt","r");
    }else if( dados == 3){
      arq = fopen("dados/file10000.txt","r");

    }else if(dados == 4){
      arq = fopen("dados/file50000.txt","r");
    }else if(dados == 5){
      arq = fopen("dados/file100000.txt","r");
    }
    else if(dados == 6){
      arq = fopen("dados/file500000.txt","r");
    }else if(dados == 7){
      arq = fopen("dados/file1000000.txt","r");
    }
    char aux[50];

    while(fgets(aux, 20,arq) != NULL){
      char tmp[20];
      int tmp_aux = 0;
      for(int i = 0 ; aux[i] != '\0' ; i++){

        if(aux[i] != ','){
          if(aux[i] != '[' && aux[i] != ']' && aux[i] != ' '){
          tmp[tmp_aux] = aux[i];

          tmp_aux++;

          }
        }else{
          tmp[tmp_aux] = '\0';

          int nmb = atoi(tmp);

          rbtInsert(&t, nmb);

          tmp_aux = 0;
        }
      }

    }

    fclose(arq);

  return t;
}

void rbtDeleteByVal(RBNode ** rbt, int key) {
    if (*rbt == NULL){
        return;
    }
    RBNode * node = Return_Node_rbtSearch(rbt, key);

    if (node->key != key) {
      return;
    }

    rbtDeleteNode(rbt, node);
 }

int rbtPreOrder(RBNode * rbt){
	if(rbt != NULL){
    int quant = 0;
		printf("%d %c, ", rbt->key, rbt->color);
		quant += rbtPreOrder(rbt->left);
		quant += rbtPreOrder(rbt->right);
    quant++;
    return quant;
	}
  return 0;
}
void rbtInOrder(RBNode * rbt){
	if(rbt != NULL){
		rbtInOrder(rbt->left);
		printf("%d", rbt->key);
		rbtInOrder(rbt->right);
	}
}
void rbtPosOrder(RBNode * rbt){
	if(rbt != NULL){
		rbtPosOrder(rbt->left);
		rbtPosOrder(rbt->right);
		printf("%d", rbt->key);
	}
}
