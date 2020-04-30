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
    Polynomial() : front(nullptr), rear(nullptr) {}
    Polynomial(const Polynomial &p) : front(nullptr), rear(nullptr) {
        Term *temp = p.front;
        front = rear = new Term(temp->exponent, temp->coefficient, temp->next);
        temp = temp->next;
        while(temp != nullptr) {
            rear->next = new Term(temp->exponent, temp->coefficient, nullptr);
            rear = rear->next;
            temp = temp->next;
        }
    }

    ~Polynomial() { 
        front = rear = nullptr;
    }

    Polynomial & operator = (const Polynomial &p) {
        delete front;
        delete rear;
        Term *temp;
        front = rear = temp = new Term(p.front->exponent, p.front->coefficient, p.front->next);
        while(temp->next != nullptr) {
            rear->next = new Term(temp->exponent, temp->coefficient, nullptr);
            temp = temp->next;
        }
        return *this;
    }

    void addTerm(int expon, int coeff) {
        if (front == nullptr ) {
            front = rear = new Term(expon, coeff, nullptr);
            
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
                else if (front->coefficient == 0 && front->next != nullptr) {
                    front = rear = nullptr;
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
                                rear = temp;
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
                        rear = temp->next;
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
         
        while (temp_p != nullptr || temp_q != nullptr) { 
            if ((temp_p != nullptr && temp_q == nullptr) || (temp_p->exponent > temp_q->exponent)) {
                pol.addTerm(temp_p->exponent, temp_p->coefficient);
                temp_p = temp_p->next;
            }
            else if (temp_p->exponent == temp_q->exponent) {
                pol.addTerm(temp_p->exponent, temp_p->coefficient + temp_q->coefficient);                temp_p = temp_p->next;
                temp_q = temp_q->next;
            }
            else if ((temp_p == nullptr && temp_q != nullptr) || (temp_p->exponent < temp_q->exponent)) {
                pol.addTerm(temp_q->exponent, temp_q->coefficient);               
                temp_q = temp_q->next;
            }
        }
        return pol;

    }
    
    friend Polynomial operator * (const Polynomial &p, const Polynomial &q) {
        Polynomial pol;
        Term *temp_p = p.front; 
        Term *temp_q = q.front;
        
        while (temp_p != nullptr) {
            while(temp_q != nullptr) {
                pol.addTerm(temp_p->exponent + temp_q->exponent, temp_p->coefficient * temp_q->coefficient);
                temp_q = temp_q->next;
            }
            temp_q = q.front;
            temp_p = temp_p ->next;
        }
        return pol;
    }

    friend ostream & operator << (ostream &out, const Polynomial &p) {
        Term *temp = p.front;
        while (temp != nullptr) {
            if (temp->exponent != p.front->exponent && temp->coefficient > 0) {
                out << " + ";
            } 
            else if (temp->coefficient < 0) {
                out << " - ";
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
        return out;
    }

private:
    Term *front, *rear;
};

int main () {
    // Polynomial p;
    // p.addTerm(1, 3);
    // p.addTerm(2, 1);
    // p.addTerm(0, -1);


    // Polynomial q(p);
    // q.addTerm(1, -3);
    // q.addTerm(4,34);
    // q.addTerm(1, 9);



    // cout << "P(x) = " << p << endl;
    // cout << "P(2) = " << p.evaluate(2) << endl;
    // cout << "Q(x) = " << q << endl;
    // cout << "Q(2) = " << q.evaluate(2) << endl;

    // cout << "(P+Q)(x) = " << p+q << endl;
    // cout << "(P*Q)(x) = " << p*q << endl;

    Polynomial p;
    p.addTerm(2, 3);
    p.addTerm(4, -1);
    p.addTerm(2, -1);
    p.addTerm(1, 6);
    p.addTerm(0, 4);
    cout << p << endl;
    cout << p.evaluate(0) << endl;
    cout << p.evaluate(1) << endl;
    cout << p.evaluate(5) << endl;
    cout << p.evaluate(10) << endl;


    Polynomial q(p);
    q.addTerm(0, -3);
    q.addTerm(1, 5);
    q.addTerm(2, -10);
    q.addTerm(2, 4);
    q.addTerm(0, 3);
    cout << q << endl;

    // cout << q.evaluate(0) << endl;
    // cout << q.evaluate(1) << endl;
    // cout << q.evaluate(5) << endl;
    // cout << q.evaluate(10) << endl;

    // Polynomial k = p+q;
    // cout << k << endl;
    // cout << k.evaluate(0) << endl;
    // cout << k.evaluate(1) << endl;
    // cout << k.evaluate(5) << endl;
    // cout << k.evaluate(10) << endl;

    // Polynomial d = p*q;
    // cout << d << endl;
    // cout << d.evaluate(0) << endl;
    // cout << d.evaluate(1) << endl;
    // cout << d.evaluate(5) << endl;
    // cout << d.evaluate(10) << endl;

    // Polynomial p;
    // p.addTerm(1, 1);
    // p.addTerm(0, -1);
    // cout << p << endl;
    // cout << p.evaluate(0) << endl;
    // cout << p.evaluate(1) << endl;
    // cout << p.evaluate(15) << endl;
    // cout << p.evaluate(1500) << endl;

    // Polynomial q;
    // q.addTerm(1, 1);
    // q.addTerm(0, 1);
    // cout << q << endl;
    // cout << q.evaluate(0) << endl;
    // cout << q.evaluate(1) << endl;
    // cout << q.evaluate(15) << endl;
    // cout << q.evaluate(1500) << endl;

    // Polynomial k = p+q;
    // cout << k << endl;
    // cout << k.evaluate(0) << endl;
    // cout << k.evaluate(1) << endl;
    // cout << k.evaluate(15) << endl;
    // cout << k.evaluate(1500) << endl;

    // Polynomial d = p*q;
    // cout << d << endl;
    // cout << d.evaluate(0) << endl;
    // cout << d.evaluate(1) << endl;
    // cout << d.evaluate(15) << endl;
    // cout << d.evaluate(1500) << endl;
}