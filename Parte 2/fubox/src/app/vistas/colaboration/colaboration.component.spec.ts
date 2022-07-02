import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ColaborationComponent } from './colaboration.component';

describe('ColaborationComponent', () => {
  let component: ColaborationComponent;
  let fixture: ComponentFixture<ColaborationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ColaborationComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ColaborationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
