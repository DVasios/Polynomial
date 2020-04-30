#include <iostream>
#include <bits/stdc++.h> 
using namespace std;


class Polynomial {
protected:
    class Term {
        public:
            friend class Polynomial;
            int exponent;
            int coefficient;
            Term *next;
            Term(int exp, int coeff, Term *n) : exponent(exp), coefficient(coeff), next(n) {}

    };

public:
    Polynomial() : front(nullptr) {}
    Polynomial(const Polynomial &p) : front(nullptr) {
        Term *temp = p.front;
        front = nullptr;
        while(temp != nullptr) {
            this->addTerm(temp->exponent, temp->coefficient);
            temp = temp->next;
        }
    }

    ~Polynomial() { 
        front = nullptr;
    }

    Polynomial & operator = (const Polynomial &p) {
        delete front;
        Term *temp = p.front;
        front = nullptr;
        while(temp != nullptr) {
            this->addTerm(temp->exponent, temp->coefficient);
            temp = temp->next;
        }
        return *this;
    }

    void addTerm(int expon, int coeff) {
        if (front == nullptr ) {
            front = new Term(expon, coeff, nullptr);
            
        }
        else {
            if (expon > front->exponent) {
                front = new Term(expon, coeff, front);
            }
            else if (expon == front->exponent) {
                front->coefficient += coeff;
                if(front->coefficient == 0 && front->next != nullptr) {
                    front = front->next;
                }
                else if (front->coefficient == 0 && front->next == nullptr) {
                    front = nullptr;
                }
            }
            else {
                bool k = true;
                Term *temp = front;
                while (k) {
                    if (temp->next != nullptr) {
                        if (temp->next->exponent > expon) {
                            temp = temp->next;
                        }
                        else if (temp->next->exponent == expon) {
                            temp->next->coefficient += coeff;
                            if (temp->next->coefficient == 0 && temp->next->next != nullptr) {
                                temp->next = temp->next->next;
                                
                            }
                            else if (temp->next->coefficient == 0 && temp->next->next == nullptr) {
                                temp->next = nullptr;
                            }
                            k = false;
                        }
                        else if (temp->next->exponent < expon) {
                            Term *p = new Term(expon, coeff, temp->next);
                            temp->next = p;
                            k = false;
                        }
                    }
                    else {
                        temp->next =  new Term(expon, coeff, nullptr);
                        k = false;
                    }
                }
                
            }
        }
    }

    double evaluate(double x) {
        double value = 0.0;
        Term *temp = front;
        while (temp != nullptr) {
            value += temp->coefficient * pow(x, temp->exponent);
            temp = temp->next;
        }
        return value;
    }

    friend Polynomial operator + (const Polynomial &p, const Polynomial &q) {
        Polynomial pol;
        Term *temp_p = p.front;
        Term *temp_q = q.front;
        pol.front = nullptr;
        if( p.front == nullptr) {
            pol = q;
        }
        else if ( q.front == nullptr) {
            pol = p;
        }
        else {
            while (temp_p != nullptr || temp_q != nullptr) { 
                if ((temp_p != nullptr && temp_q == nullptr)) {
                    pol.addTerm(temp_p->exponent, temp_p->coefficient);
                    temp_p = temp_p->next;
                }
                else if ((temp_p == nullptr && temp_q != nullptr)) {
                    pol.addTerm(temp_q->exponent, temp_q->coefficient);               
                    temp_q = temp_q->next;
                }
                else if ((temp_p->exponent > temp_q->exponent)) {
                    pol.addTerm(temp_p->exponent, temp_p->coefficient);
                    temp_p = temp_p->next;
                }
                else if ((temp_p->exponent < temp_q->exponent)) {
                    pol.addTerm(temp_q->exponent, temp_q->coefficient);               
                    temp_q = temp_q->next;
                }
                else if (temp_p->exponent == temp_q->exponent) {
                    if (temp_p->coefficient + temp_q->coefficient == 0) {
                        temp_p = temp_p->next;
                        temp_q = temp_q->next;
                    }
                    else {
                        pol.addTerm(temp_p->exponent, temp_p->coefficient + temp_q->coefficient);                
                        temp_p = temp_p->next;
                        temp_q = temp_q->next;
                    }
                }
            }
        }
        return pol;

    }
    
    friend Polynomial operator * (const Polynomial &p, const Polynomial &q) {
        Polynomial pol;
        Term *temp_p = p.front; 
        Term *temp_q = q.front;
        pol.front == nullptr;
        if ( p.front != nullptr || q.front != nullptr) {
            while (temp_p != nullptr) {
                while(temp_q != nullptr) {
                    pol.addTerm(temp_p->exponent + temp_q->exponent, temp_p->coefficient * temp_q->coefficient);
                    temp_q = temp_q->next;
                }
                temp_q = q.front;
                temp_p = temp_p ->next;
            }
        }
        return pol;
    }

    friend ostream & operator << (ostream &out, const Polynomial &p) {
        Term *temp = p.front;
        if (p.front == nullptr) cout << "0";
        else {
            while (temp != nullptr) {
                if (temp->exponent != p.front->exponent) cout << " ";
                if (temp->exponent != p.front->exponent && temp->coefficient > 0) {
                    out << "+ ";
                }   
                else if (temp->coefficient < 0) {
                    out << "- ";
                }
                if (abs(temp->coefficient) == 1) {
                    if (abs(temp->exponent) == 1) {
                        out << "x";
                        temp = temp->next;
                    }
                    else if (temp->exponent == 0 ) {
                        out << abs(temp->coefficient);
                        temp = temp->next;
                    }
                    else {
                        out << "x^" << temp->exponent;
                        temp = temp->next;       
                    }
                }
                else if (temp->coefficient == 0) {
                    temp = temp->next;
                }
                else {   
                    if (temp->exponent == 0 ) {
                        out << abs(temp->coefficient);
                        temp = temp->next;
                    }
                    else if (temp->exponent == 1) {
                        out << abs(temp->coefficient) << "x";
                        temp = temp->next;
                    }
                    else {
                        out << abs(temp->coefficient) << "x^" << temp->exponent;
                        temp = temp->next;
                    }
                }
            }
        }
        return out;
    }

private:
    Term *front;
};


int main () {
    Polynomial p;
    p.addTerm(6, -22);
    p.addTerm(10, 1);
    p.addTerm(2, 4);
    //p.addTerm(1, 1);
    cout << "P(X) = " << p << endl;
    cout << "P(0) = " << p.evaluate(0) << endl;
    cout << "P(1) = " << p.evaluate(1) << endl;
    cout << "P(3) = " << p.evaluate(3) << endl;
    cout << "P(-8) = " << p.evaluate(-8) << endl;
    cout << endl;

    Polynomial q;
    q.addTerm(1, 3);
    q.addTerm(2, -9);
    q.addTerm(1, 5);
    q.addTerm(0, 7);
    cout << "Q(X) = " << q << endl;
    cout << "Q(0) = " << q.evaluate(0) << endl;
    cout << "Q(1) = " << q.evaluate(1) << endl;
    cout << "Q(3) = " << q.evaluate(3) << endl;
    cout << "Q(-8) = " << q.evaluate(-8) << endl;
    cout << endl;

    cout << "(P+Q)(x) = " << p+q << endl;
    cout << "(P*Q)(x) = " << p*q << endl;
    
}