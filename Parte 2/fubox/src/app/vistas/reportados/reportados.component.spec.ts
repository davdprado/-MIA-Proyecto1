import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ReportadosComponent } from './reportados.component';

describe('ReportadosComponent', () => {
  let component: ReportadosComponent;
  let fixture: ComponentFixture<ReportadosComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ReportadosComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ReportadosComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
