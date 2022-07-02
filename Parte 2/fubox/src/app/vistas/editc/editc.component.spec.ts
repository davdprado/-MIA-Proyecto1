import { ComponentFixture, TestBed } from '@angular/core/testing';

import { EditcComponent } from './editc.component';

describe('EditcComponent', () => {
  let component: EditcComponent;
  let fixture: ComponentFixture<EditcComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ EditcComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(EditcComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
